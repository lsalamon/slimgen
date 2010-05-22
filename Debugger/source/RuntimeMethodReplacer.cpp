/*
* Copyright (c) 2007-2010 SlimGen Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include "stdafx.h"

#include "RuntimeMethodReplacer.h"
#include "SigFormat.h"

namespace SlimGen
{
    template<class T> std::wstring GetName(T* ptr)
    {
        ULONG32 nameLen = 0;
        ptr->GetName(nameLen, &nameLen, 0);

        std::wstring name(nameLen, 0);
        ptr->GetName(nameLen, &nameLen, &name[0]);

        return std::wstring(name.begin(), name.end() - 1);
    }

    void RuntimeMethodReplacer::Run(int processId, std::wstring const& runtimeVersion)
    {
        if (FAILED(CoInitialize(0)))
            throw std::runtime_error("Unable to initialize COM.");

        waitForSlimGen.Reset(CreateEvent(0, TRUE, FALSE, 0));
        std::wstring version = runtimeVersion;//GetRuntimeVersion(processId);

        CComPtr<ICorDebug> corDebug;
        if (FAILED(CreateDebuggingInterfaceFromVersion(CorDebugLatestVersion, version.c_str(), reinterpret_cast<IUnknown**>(&corDebug.p))))
            throw std::runtime_error("Unable to create debugging interface from version.");

        if (FAILED(corDebug->Initialize()))
            throw std::runtime_error("Unable to initialize debugging interface.");

        if (FAILED(corDebug->SetManagedHandler(this)))
            throw std::runtime_error("Unable to set managed debugger callback.");

        if (FAILED(corDebug->DebugActiveProcess(processId, FALSE, &debugProcess.p)))
            throw std::runtime_error("Unable to attach to process for debugging.");

        WaitForSingleObject(waitForSlimGen, INFINITE);
        corDebug->Terminate();
        CoUninitialize();
    }

    void RuntimeMethodReplacer::ReplaceMethod(ICorDebugFunction* function, MethodReplacement method)
    {
        std::string name(method.Method.begin(), method.Method.end());
        MessageBoxA(0, name.c_str(), "", MB_OK);
        if (method.Replaced)
            throw std::runtime_error(std::string("Attempt to replace method ") + name + " multiple times.");

        CComPtr<ICorDebugCode> codePtr;
        function->GetNativeCode(&codePtr.p);
        CComQIPtr<ICorDebugCode2> code2Ptr(codePtr);

        ULONG32 chunkCount;
        code2Ptr->GetCodeChunks(0, &chunkCount, 0);
        std::vector<CodeChunkInfo> chunks(chunkCount);
        code2Ptr->GetCodeChunks(chunkCount, &chunkCount, &chunks[0]);

        if (method.CompiledData.size() != chunkCount)
            throw std::runtime_error(name + " does not have the correct number of code chunks.");

        for (size_t i = 0; i < chunks.size(); i++)
        {
            if (method.CompiledData[i].size() != chunks[i].length)
            {
                std::stringstream error;
                error << "Chunk " << i << " for method " << name << " does not have the right code size.";
                throw std::runtime_error(error.str());
            }

            SIZE_T written;
            debugProcess->WriteMemory(chunks[i].startAddr, chunks[i].length, reinterpret_cast<BYTE*>(&method.CompiledData[i][0]), &written);

            if (written != chunks[i].length)
            {
                std::stringstream error;
                error << "Chunk " << i << " for method " << name << " failed to write completely.";
                throw std::runtime_error(error.str());
            }
        }

        method.Replaced = true;
    }

    bool RuntimeMethodReplacer::VisitAssemblyHandler(ICorDebugAssembly*, const std::wstring& name)
    {
        for (size_t i = 0; i < methods.size(); i++)
        {
            if(methods[i].Assembly == name)
                return true;
        }

        return true;
    }

    void RuntimeMethodReplacer::VisitFunctionHandler(ICorDebugFunction* function, const std::wstring& signature)
    {
        if(signature.find(L"DotProduct") != signature.npos) {
            std::wcout<<signature<<std::endl;
        }

        for(size_t i = 0; i < methods.size(); i++)
        {

            if(signature == methods[i].Method)
            {
                MessageBox(0, L"Visit Method", L"", MB_OK);
                ReplaceMethod(function, methods[i]);
                break;
            }
        }
    }

    HRESULT STDMETHODCALLTYPE RuntimeMethodReplacer::CreateAppDomain(ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain)
    {
        pAppDomain->Attach();
        pProcess->Continue(FALSE);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE RuntimeMethodReplacer::Break(ICorDebugAppDomain* appDomain, ICorDebugThread*)
    {
        ULONG assemblyCount;
        ICorDebugAssembly* assembly;
        ICorDebugAssemblyEnum* assemblyEnum;

        appDomain->EnumerateAssemblies(&assemblyEnum);
        assemblyEnum->Next(1, &assembly, &assemblyCount);

        while (assemblyCount)
        {
            if (!VisitAssemblyHandler(assembly, GetName(assembly)))
            {
                assembly->Release();
                assemblyEnum->Next(1, &assembly, &assemblyCount);
                continue;
            }

            ULONG moduleCount;
            ICorDebugModule* module;
            ICorDebugModuleEnum* moduleEnum;

            assembly->EnumerateModules(&moduleEnum);
            moduleEnum->Next(1, &module, &moduleCount);

            while (moduleCount)
            {
                IMetaDataImport2* meta;
                HCORENUM typeEnum = 0;
                mdTypeDef type;
                ULONG typeCount;

                module->GetMetaDataInterface(IID_IMetaDataImport2, reinterpret_cast<IUnknown**>(&meta));
                meta->EnumTypeDefs(&typeEnum, &type, 1, &typeCount);

                while (typeCount)
                {
                    HCORENUM methodEnum = 0;
                    mdMethodDef method;
                    ULONG methodCount;
                    std::wstring typeName = GetTypeNameFromDef(meta, type);

                    meta->EnumMethods(&methodEnum, type, &method, 1, &methodCount);
                    while (methodCount)
                    {
                        ICorDebugFunction* function;
                        module->GetFunctionFromToken(method, &function);
                        std::wstring methodName = GetMethodNameFromDef(meta, method);
                        VisitFunctionHandler(function, typeName + L"." + methodName);

                        function->Release();
                        meta->EnumMethods(&methodEnum, type, &method, 1, &methodCount);
                    }

                    meta->CloseEnum(methodEnum);

                    meta->EnumTypeDefs(&typeEnum, &type, 1, &typeCount);
                }

                meta->CloseEnum(typeEnum);
                meta->Release();

                module->Release();
                moduleEnum->Next(1, &module, &moduleCount);
            }

            moduleEnum->Release();
            assembly->Release();
            assemblyEnum->Next(1, &assembly, &assemblyCount);
        }

        assemblyEnum->Release();
        appDomain->Continue(FALSE);
        appDomain->Detach();
        debugProcess->Detach();
        SetEvent(waitForSlimGen);

        return S_OK;
    }

    std::wstring RuntimeMethodReplacer::GetMethodNameFromDef( IMetaDataImport2* metadata, mdMethodDef methodDef)
    {
        ULONG methodNameLength;
        PCCOR_SIGNATURE signature;
        ULONG signatureLength;
        metadata->GetMethodProps(methodDef, 0, 0, 0, &methodNameLength, 0, 0, 0, 0, 0);

        std::wstring methodName(methodNameLength, 0);
        std::wstring signatureStr;
        metadata->GetMethodProps(methodDef, 0, &methodName[0], methodNameLength, &methodNameLength, 0, &signature, &signatureLength, 0, 0);

        wchar_t sigStr[2048];
        SigFormat formatter(sigStr, 2048, methodDef, metadata, metadata);
        formatter.Parse(static_cast<const sig_byte*>(signature), signatureLength);
        signatureStr = sigStr;

        return methodName.substr(0, methodName.length() - 1) + signatureStr;
    }

    std::wstring RuntimeMethodReplacer::GetTypeNameFromDef(IMetaDataImport2* metadata, mdTypeDef typeDef)
    {
        ULONG typeNameLength;
        metadata->GetTypeDefProps(typeDef, 0, 0, &typeNameLength, 0, 0);

        std::wstring typeName(typeNameLength, 0);
        metadata->GetTypeDefProps(typeDef, &typeName[0], typeNameLength, &typeNameLength, 0, 0);

        return std::wstring(typeName.begin(), typeName.end() - 1);
    }

    std::wstring GetRuntimeVersion(int processId)
    {
        Handle handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
        if (handle.IsInvalid())
            throw std::runtime_error("Unable to open process.");

        std::wstringstream wss;
        wss<<std::hex<<handle<<std::endl<<processId;
        MessageBox(0, wss.str().c_str(), L"Test", MB_OK);

        DWORD length;
        if (FAILED(GetVersionFromProcess(handle, NULL, 0, &length)))
            throw std::runtime_error("Unable to get version length from process.");

        std::wstring version(length, 0);
        if (FAILED(GetVersionFromProcess(handle, &version[0], length, &length)))
            throw std::runtime_error("Unable to get version from process.");

        return version;
    }
}