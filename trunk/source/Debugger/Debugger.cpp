/*
* Copyright (c) 2007-2009 SlimGen Group
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

#include "..\stdafx.h"
#include "Debugger.h"

namespace SlimGen {
	HRESULT STDMETHODCALLTYPE Debugger::CreateAppDomain( ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain )
	{
		pAppDomain->Attach();
		pAppDomain->Continue(FALSE);
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE Debugger::Break( ICorDebugAppDomain *pAppDomain, ICorDebugThread *thread )
	{
		EnumerateAssemblies(pAppDomain);

		pAppDomain->Continue(FALSE);
		return S_OK;
	}

	void Debugger::EnumerateAssemblies( ICorDebugAppDomain * pAppDomain )
	{
		CComPtr<ICorDebugAssemblyEnum> assemblyEnum;
		pAppDomain->EnumerateAssemblies(&assemblyEnum);
		ULONG numberOfAssemblies;
		assemblyEnum->GetCount(&numberOfAssemblies);

		std::vector<CComPtr<ICorDebugAssembly> > assemblies(numberOfAssemblies);
		assemblyEnum->Next(assemblies.size(), &assemblies[0], &numberOfAssemblies);

		for(std::size_t i = 0; i < assemblies.size(); ++i) {
			ULONG32 nameLength;
			assemblies[i]->GetName(0, &nameLength, 0);
			std::wstring assemblyName(nameLength, '\0');
			assemblies[i]->GetName(nameLength, &nameLength, &assemblyName[0]);
			EnumerateModules(assemblies[i]);
		}
	}

	void Debugger::EnumerateModules( CComPtr<ICorDebugAssembly> assembly )
	{
		CComPtr<ICorDebugModuleEnum> moduleEnum;
		assembly->EnumerateModules(&moduleEnum);

		ULONG numberOfModules;
		moduleEnum->GetCount(&numberOfModules);
		std::vector<CComPtr<ICorDebugModule> > modules(numberOfModules);
		moduleEnum->Next(modules.size(), &modules[0], &numberOfModules);

		for(std::size_t j = 0; j < modules.size(); ++j) {
			CComPtr<ICorDebugModule> module = modules[j];
			CComPtr<IMetaDataImport2> metadata;
			module->GetMetaDataInterface(IID_IMetaDataImport2, reinterpret_cast<IUnknown**>(&metadata));

			EnumerateTypes(metadata, module);
		}
	}

	void Debugger::EnumerateTypes( CComPtr<IMetaDataImport2> metadata, CComPtr<ICorDebugModule> module )
	{
		HCORENUM typeEnum = 0;
		mdTypeDef typeDef;
		ULONG typeCount;
		do {
			metadata->EnumTypeDefs(&typeEnum, &typeDef, 1, &typeCount);
			std::wstring typeName = GetTypeNameFromDef(metadata, typeDef);

			EnumerateMethods(metadata, typeDef, module, typeName);

		} while(typeCount > 0);
		metadata->CloseEnum(typeEnum);
	}

	void Debugger::EnumerateMethods( CComPtr<IMetaDataImport2> metadata, mdTypeDef typeDef, CComPtr<ICorDebugModule> module, std::wstring const& typeName )
	{
		HCORENUM methodEnum = 0;
		mdMethodDef methodDef;
		ULONG methodCount;
		do {
			metadata->EnumMethods(&methodEnum, typeDef, &methodDef, 1, &methodCount);

			if(!HasAttribute(metadata, methodDef))
				continue;

			CComPtr<ICorDebugFunction> function;
			module->GetFunctionFromToken(methodDef, &function);

			std::wstring methodName = GetMethodNameFromDef(metadata, methodDef);
			CComPtr<ICorDebugCode> nativeCode;
			function->GetNativeCode(&nativeCode);

			if(nativeCode == 0) {
				std::wcout<<"Warning: Method marked as ["
					<<L"ScapeCode.Generator.ReplaceMethodNativeAttribute"
					<<"] but does not have native code: "
					<<typeName<<"."<<methodName<<std::endl;
			}

			CComPtr<ICorDebugCode2> nativeCode2;
			nativeCode->QueryInterface(IID_ICorDebugCode2, reinterpret_cast<void**>(&nativeCode2));

			ULONG32 numberOfCodeChunks;
			nativeCode2->GetCodeChunks(0, &numberOfCodeChunks, 0);
			std::vector<CodeChunkInfo> codeChunks(numberOfCodeChunks);
			nativeCode2->GetCodeChunks(numberOfCodeChunks, &numberOfCodeChunks, &codeChunks[0]);

			MethodNativeBlocks block = {0, methodName, codeChunks};
			module->GetBaseAddress(&block.BaseAddress);

			methodBlocks.push_back(block);
		} while(methodCount > 0);
		metadata->CloseEnum(methodEnum);
	}

	std::wstring Debugger::GetTypeNameFromDef( CComPtr<IMetaDataImport2> metadata, mdTypeDef typeDef )
	{
		wchar_t typeName[256];
		ULONG typeNameLength;
		DWORD flags;
		mdToken extends;
		metadata->GetTypeDefProps(typeDef, typeName, 256, &typeNameLength, &flags, &extends);
		return typeName;
	}

	std::wstring Debugger::GetMethodNameFromDef( CComPtr<IMetaDataImport2> metadata, mdMethodDef methodDef )
	{
		mdTypeDef outMethodType;
		wchar_t methodName[256];
		ULONG methodNameLength;
		DWORD attributes;
		PCCOR_SIGNATURE signature;
		ULONG signatureLength;
		ULONG codeRVA;
		DWORD implFlags;
		metadata->GetMethodProps(methodDef, &outMethodType,methodName, 256, &methodNameLength, &attributes, &signature, &signatureLength, &codeRVA, &implFlags);
		return methodName;
	}

	bool Debugger::HasAttribute( CComPtr<IMetaDataImport2> metadata, mdMethodDef methodDef )
	{
		const void* attribData;
		ULONG dataLen;
		metadata->GetCustomAttributeByName(methodDef, L"ScapeCode.Generator.ReplaceMethodNativeAttribute", &attribData, &dataLen);

		return dataLen > 0;
	}
}