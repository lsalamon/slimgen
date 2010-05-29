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

#include "MethodIterator.h"
#include "SigFormat.h"

namespace SlimGen {
    void MethodIterator::Run(int processId, std::wstring const& runtimeVersion) {
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

    bool MethodIterator::VisitAssemblyHandler(ICorDebugAssembly*, const std::wstring& name) {
        for (size_t i = 0; i < methods.size(); i++) {
            if(methods[i].Assembly == name)
                return true;
        }

        return true;
    }

    void MethodIterator::VisitFunctionHandler(ICorDebugFunction* function, const std::wstring& signature) {
        if(signature.find(L"DotProduct") != signature.npos) {
            std::wcout<<signature<<std::endl;
        }

        for(size_t i = 0; i < methods.size(); i++) {

            if(signature == methods[i].Method) {
                FoundMethod(function, methods[i]);
                break;
            }
        }
    }

    HRESULT STDMETHODCALLTYPE MethodIterator::CreateAppDomain(ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain) {
        pAppDomain->Attach();
        pProcess->Continue(FALSE);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE MethodIterator::Break(ICorDebugAppDomain* appDomain, ICorDebugThread*) {
        ULONG assemblyCount;
        ICorDebugAssembly* assembly;
        ICorDebugAssemblyEnum* assemblyEnum;

        appDomain->EnumerateAssemblies(&assemblyEnum);
        assemblyEnum->Next(1, &assembly, &assemblyCount);

        while (assemblyCount) {
            if (!VisitAssemblyHandler(assembly, GetName(assembly))) {
                assembly->Release();
                assemblyEnum->Next(1, &assembly, &assemblyCount);
                continue;
            }

            ULONG moduleCount;
            ICorDebugModule* module;
            ICorDebugModuleEnum* moduleEnum;

            assembly->EnumerateModules(&moduleEnum);
            moduleEnum->Next(1, &module, &moduleCount);

            while (moduleCount) {
                IMetaDataImport2* meta;
                HCORENUM typeEnum = 0;
                mdTypeDef type;
                ULONG typeCount;

                module->GetMetaDataInterface(IID_IMetaDataImport2, reinterpret_cast<IUnknown**>(&meta));
                meta->EnumTypeDefs(&typeEnum, &type, 1, &typeCount);

                while (typeCount) {
                    HCORENUM methodEnum = 0;
                    mdMethodDef method;
                    ULONG methodCount;
                    std::wstring typeName = GetTypeNameFromDef(meta, type);

                    meta->EnumMethods(&methodEnum, type, &method, 1, &methodCount);
                    while (methodCount) {
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
}