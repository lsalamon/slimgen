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

#include <Windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <cor.h>
#include <cordebug.h>
#include <vector>
#include <iostream>
#include <string>
#include <psapi.h>
#include <mscoree.h>

#include "Debugger.h"


std::wstring const MethodReplacementAttribute = L"SlimGen.Generator.ReplaceMethodNativeAttribute";

namespace SlimGen {
	Debugger::Debugger(std::wstring assemblySimpleName) : assemblySimpleName(assemblySimpleName) {
	}

	HRESULT STDMETHODCALLTYPE Debugger::CreateAppDomain( ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain )
	{
		pAppDomain->Attach();
		pProcess->Continue(FALSE);
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE Debugger::Break( ICorDebugAppDomain *pAppDomain, ICorDebugThread *thread )
	{
		CComPtr<ICorDebugProcess> process;
		pAppDomain->GetProcess(&process);
		HPROCESS processHandle;
		process->GetHandle(&processHandle);

		std::vector<HMODULE> moduleHandles;
		DWORD numberOfBytesNeeded;
		EnumProcessModules(processHandle, 0, 0, &numberOfBytesNeeded);
		moduleHandles.resize(numberOfBytesNeeded / sizeof(HMODULE));
		EnumProcessModules(processHandle, &moduleHandles[0], moduleHandles.size() * sizeof(HMODULE), &numberOfBytesNeeded);

		for(std::size_t i = 0; i < moduleHandles.size(); ++i) {
			std::wstring moduleFileName(MAX_PATH, L'\0');
			GetModuleFileNameEx(processHandle, moduleHandles[i], &moduleFileName[0], MAX_PATH);
			std::locale loc;
			std::use_facet<std::ctype<wchar_t> > (loc).tolower(&moduleFileName[0], &moduleFileName[moduleFileName.size()]);
			if(moduleFileName.find(L"nativeimages") != moduleFileName.npos && moduleFileName.find(assemblySimpleName) != moduleFileName.npos) {
				nativeImageName = moduleFileName.c_str();
#ifdef _DEBUG
				std::wcout<<moduleFileName.c_str()<<std::endl;
#endif
			}
		}

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
					<<MethodReplacementAttribute
					<<"] but does not have native code: "
					<<typeName<<"."<<methodName<<std::endl;
			}

			CComPtr<ICorDebugCode2> nativeCode2;
			nativeCode->QueryInterface(IID_ICorDebugCode2, reinterpret_cast<void**>(&nativeCode2));

			ULONG32 numberOfCodeChunks;
			nativeCode2->GetCodeChunks(0, &numberOfCodeChunks, 0);
			std::vector<CodeChunkInfo> codeChunks(numberOfCodeChunks);
			nativeCode2->GetCodeChunks(numberOfCodeChunks, &numberOfCodeChunks, &codeChunks[0]);

			MethodNativeBlocks block = {0, typeName + L"." + methodName, codeChunks};
			module->GetBaseAddress(&block.BaseAddress);

			methodBlocks.push_back(block);
		} while(methodCount > 0);
		metadata->CloseEnum(methodEnum);
	}

	std::wstring const& Debugger::GetNativeImagePath() const {
		return nativeImageName;
	}

	std::vector<MethodNativeBlocks> const& Debugger::GetNativeMethodBlocks() const {
		return methodBlocks;
	}

	std::wstring Debugger::GetTypeNameFromDef( CComPtr<IMetaDataImport2> metadata, mdTypeDef typeDef ) {
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

	bool Debugger::HasAttribute( CComPtr<IMetaDataImport2> metadata, mdMethodDef methodDef ) {
		const void* attribData = 0;
		ULONG dataLen = 0;
		metadata->GetCustomAttributeByName(methodDef, MethodReplacementAttribute.c_str(), &attribData, &dataLen);

		return dataLen > 0;
	}

	/*
	This is a particularly brittle method, it is designed to take in the following types of inputs and return the results indicated:
	"SlimDX, Culture=en, PublicKeyToken=a5d015c7d5a0b012, Version=1.0.0.0"
	returns "slimdx"
	"C:\Projects\SlimDX\Build\x86\release\SlimDX.dll"
	returns "slimdx"
	"C:/Projects/SlimDX/Build/x86/release/SlimDX.dll"
	returns "slimdx"
	*/
	std::wstring GetSimpleAssemblyName(std::wstring assemblyName) {
		std::wstring result;
		if(assemblyName.find(L",") != assemblyName.npos) {
			result = assemblyName.substr(0, assemblyName.find(L","));
		} else {
			if(assemblyName.find_last_of(L"\\") != assemblyName.npos) {
				result = assemblyName.substr(assemblyName.find_last_of(L"\\") + 1);
				if(result.find(L"."))
					result = result.substr(0, result.find(L"."));
			} else if(assemblyName.find_last_of(L"/")) {
				result = assemblyName.substr(assemblyName.find_last_of(L"/") + 1);
				if(result.find(L"."))
					result = result.substr(0, result.find(L"."));
			}
		}

		std::locale loc;
		std::use_facet<std::ctype<wchar_t> >(loc).tolower(&result[0], &result[result.size()]);
		return result;
	}

	class ComInit {
	public:
		ComInit() { CoInitialize(0); }
		~ComInit() { CoUninitialize(); }
	};

	std::pair<std::wstring, std::vector<SlimGen::MethodNativeBlocks>> GetNativeImageInformation( wchar_t* assemblyName )
	{
		ComInit cominit;
		SlimGen::Debugger debuggerCallback(GetSimpleAssemblyName(assemblyName));

		wchar_t runtimeVersion[256];
		DWORD runtimeVersionLength;
		GetRequestedRuntimeVersion(L"HostProcess.exe", runtimeVersion, 256, &runtimeVersionLength);

		CComPtr<ICorDebug> debug;
		if(FAILED(CreateDebuggingInterfaceFromVersion(CorDebugLatestVersion, runtimeVersion, reinterpret_cast<IUnknown**>(&debug)))) {
			std::wcout<<L"Unable to create debugging interface."<<std::endl;
			return std::pair<std::wstring const, std::vector<SlimGen::MethodNativeBlocks>>();
		}

		if(FAILED(debug->Initialize())) {
			std::wcout<<L"Unable to initialize debugger."<<std::endl;
			return std::pair<std::wstring const, std::vector<SlimGen::MethodNativeBlocks>>();
		}

		if(FAILED(debug->SetManagedHandler(&debuggerCallback))) {
			std::wcout<<L"Unable to configure debugger callback."<<std::endl;
			return std::pair<std::wstring const, std::vector<SlimGen::MethodNativeBlocks>>();
		}

		wchar_t commandLine[MAX_PATH];
		std::wstring commandLineStr = L"HostProcess.exe \"";
		commandLineStr += assemblyName;
		commandLineStr += L"\"";

		wcsncpy_s(commandLine, MAX_PATH, commandLineStr.c_str(), commandLineStr.size());

		STARTUPINFO startInfo = {};
		startInfo.cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION pi = {};

		CComPtr<ICorDebugProcess> process;
		if(FAILED(debug->CreateProcess(L"HostProcess.exe", commandLine, 0, 0, FALSE, 0, 0, 0, &startInfo, &pi, DEBUG_NO_SPECIAL_OPTIONS, &process))) {
			std::wcout<<L"Unable to create process."<<std::endl;
			return std::pair<std::wstring const, std::vector<SlimGen::MethodNativeBlocks>>();
		}

		WaitForSingleObject(pi.hProcess, INFINITE);

		return std::make_pair(debuggerCallback.GetNativeImagePath(), debuggerCallback.GetNativeMethodBlocks());
	}
}