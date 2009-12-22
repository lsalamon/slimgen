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

#include "stdafx.h"

#include "SigFormat.h"
#include "Debugger.h"

namespace SlimGen {
	template<class T> std::wstring GetName(T* ptr) {
		ULONG32 nameLen = 0;
		ptr->GetName(nameLen, &nameLen, 0);
		std::wstring name(nameLen, 0);
		ptr->GetName(nameLen, &nameLen, &name[0]);
		return std::wstring(name.begin(), name.end() - 1);
	}

	HRESULT STDMETHODCALLTYPE Debugger::CreateAppDomain( ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain )
	{
		pAppDomain->Attach();
		pProcess->Continue(FALSE);
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE Debugger::Break(ICorDebugAppDomain* appDomain, ICorDebugThread* thread) {
		ULONG assemblyCount;
		ICorDebugAssembly* assembly;
		ICorDebugAssemblyEnum* assemblyEnum;

		appDomain->EnumerateAssemblies(&assemblyEnum);

		assemblyEnum->Next(1, &assembly, &assemblyCount);

		while(assemblyCount) {
			if(!visitAssemblyHandler.empty()) {
				if(!visitAssemblyHandler(assembly, GetName(assembly))) {
					assembly->Release();
					assemblyEnum->Next(1, &assembly, &assemblyCount);
					continue;
				}
			}

			ULONG moduleCount;
			ICorDebugModule* module;
			ICorDebugModuleEnum* moduleEnum;

			assembly->EnumerateModules(&moduleEnum);

			moduleEnum->Next(1, &module, &moduleCount);

			while(moduleCount) {
				if(!visitModuleHandler.empty()) {
					if(!visitModuleHandler(module, GetName(module))) {
						module->Release();
						moduleEnum->Next(1, &module, &moduleCount);
						continue;
					}
				}

				IMetaDataImport2* meta;
				HCORENUM typeEnum = 0;
				mdTypeDef type;
				ULONG typeCount;

				module->GetMetaDataInterface(IID_IMetaDataImport2, reinterpret_cast<IUnknown**>(&meta));
				meta->EnumTypeDefs(&typeEnum, &type, 1, &typeCount);
				while(typeCount) {
					HCORENUM methodEnum = 0;
					mdMethodDef method;
					ULONG methodCount;
					std::wstring typeName = GetTypeNameFromDef(meta, type);
					bool handleType = true;
					if(!visitTypeHandler.empty())
						handleType = visitTypeHandler(typeName);

					if(handleType) {
						meta->EnumMethods(&methodEnum, type, &method, 1, &methodCount);
						while(methodCount) {
							ICorDebugFunction* function;
							std::wstring methodName;
							methodName = GetMethodNameFromDef(meta, method);
							module->GetFunctionFromToken(method, &function);

							if(!visitFunctionHandler.empty())
								visitFunctionHandler(function, methodName);

							function->Release();
							meta->EnumMethods(&methodEnum, type, &method, 1, &methodCount);
						}
						meta->CloseEnum(methodEnum);
					}
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

		if(!visitDoneParsing.empty())
			visitDoneParsing(appDomain);

		return S_OK;
	}

	std::wstring Debugger::GetMethodNameFromDef( IMetaDataImport2* metadata, mdMethodDef methodDef)
	{
		ULONG methodNameLength;
		PCCOR_SIGNATURE signature;
		ULONG signatureLength;
		metadata->GetMethodProps(methodDef, 0, 0, 0, &methodNameLength, 0, 0, 0, 0, 0);
		std::wstring methodName(methodNameLength, 0);
		std::wstring signatureStr;
		metadata->GetMethodProps(methodDef, 0, &methodName[0], methodName.length(), &methodNameLength, 0, &signature, &signatureLength, 0, 0);
		wchar_t sigStr[2048];
		SigFormat formatter(sigStr, 2048, methodDef, metadata, metadata);
		formatter.Parse(static_cast<sig_byte const*>(signature), signatureLength);
		signatureStr = sigStr;
		return (methodName.substr(0, methodName.length() - 1) + signatureStr);
	}

	std::wstring Debugger::GetTypeNameFromDef( IMetaDataImport2* metadata, mdTypeDef typeDef)
	{
		ULONG typeNameLength;
		metadata->GetTypeDefProps(typeDef, 0, 0, &typeNameLength, 0, 0);
		std::wstring typeName(typeNameLength, 0);
		metadata->GetTypeDefProps(typeDef, &typeName[0], typeName.length(), &typeNameLength, 0, 0);
		return std::wstring(typeName.begin(), typeName.end() - 1);
	}

	std::wstring GetRuntimeVersionFromFile(std::wstring const& filename) {
		DWORD len;
		std::wstring tmpFilename = filename;
		GetRequestedRuntimeVersion(&tmpFilename[0], 0, 0, &len);
		std::wstring version(len, 0);
		if(FAILED(GetRequestedRuntimeVersion(&tmpFilename[0], &version[0], len, &len)))
			throw std::runtime_error("unable to get version from process.");
		return version;
	}
}