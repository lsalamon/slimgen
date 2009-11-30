#include <cor.h>
#include <cordebug.h>
#include <MSCorEE.h>

#include <string>
#include <iostream>
#include <vector>

#include "DebuggerImpl.h"
#include "SigFormat.h"

namespace SlimGen {
	class Debugger : public DebuggerImpl {
	public:
		HRESULT STDMETHODCALLTYPE Debugger::CreateAppDomain( ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain )
		{
			pAppDomain->Attach();
			pProcess->Continue(FALSE);
			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE LoadModule(ICorDebugAppDomain *pAppDomain, ICorDebugModule *pModule) {
			std::wstring name = GetName(pModule);
			std::wcout<<L"Module: "<<name<<std::endl;
			if(name.find(L"SlimGenTest") != name.npos)
				modules.push_back(pModule);

			pAppDomain->Continue(FALSE);
			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE Break(ICorDebugAppDomain* appDomain, ICorDebugThread* thread) {
			for(std::size_t i = 0; i < modules.size(); ++i) {
				IMetaDataImport2* meta;
				modules[i]->GetMetaDataInterface(IID_IMetaDataImport2, reinterpret_cast<IUnknown**>(&meta));
				HCORENUM typeEnum = 0;
				mdTypeDef types[256];
				ULONG typeCount;
				meta->EnumTypeDefs(&typeEnum, types, 256, &typeCount);
				for(ULONG j = 0; j < typeCount; ++j) {
					HCORENUM methodEnum = 0;
					mdMethodDef methods[256];
					ULONG methodCount;
					meta->EnumMethodsWithName(&methodEnum, types[j], L"DotProduct", methods, 256, &methodCount);
					if(methodCount > 0) {
						ICorDebugFunction* function;
						std::wstring methodName;
						methodName = GetMethodNameFromDef(meta, methods[0]);
						std::wcout<<methodName<<std::endl;
						modules[i]->GetFunctionFromToken(methods[0], &function);
						ICorDebugCode* code;
						function->GetNativeCode(&code);
						ICorDebugCode2* code2;
						code->QueryInterface(IID_ICorDebugCode2, reinterpret_cast<void**>(&code2));
						CodeChunkInfo chunks[256];
						ULONG32 chunkLen = 256;
						code2->GetCodeChunks(chunkLen, &chunkLen, chunks);
						code->Release();
						function->Release();
					}
					meta->CloseEnum(methodEnum);
				}
				meta->CloseEnum(typeEnum);
				meta->Release();
			}

			appDomain->Continue(FALSE);
			return S_OK;
		}

	private:
		template<class T> std::wstring GetName(T* ptr) {
			ULONG32 nameLen = 0;
			ptr->GetName(nameLen, &nameLen, 0);
			std::wstring name(nameLen, 0);
			ptr->GetName(nameLen, &nameLen, &name[0]);
			return name;
		}

		std::wstring GetMethodNameFromDef( IMetaDataImport2* metadata, mdMethodDef methodDef)
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

		std::vector<ICorDebugModule*> modules;
	};

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



int wmain(int argc, wchar_t* argv) {
	CoInitialize(0);
	std::wstring processName = L"SlimGenTest.exe";
	std::wstring commandLine = L"SlimGenTest.exe";
	std::wstring version = SlimGen::GetRuntimeVersionFromFile(processName);

	ICorDebug* corDebug;
	CreateDebuggingInterfaceFromVersion(CorDebugLatestVersion, version.c_str(), reinterpret_cast<IUnknown**>(&corDebug));

	if(FAILED(corDebug->Initialize())) {
		std::wcout<<"Failed - Initialize";
		corDebug->Release();
		return 0;
	}
	SlimGen::Debugger debugger;
	if(FAILED(corDebug->SetManagedHandler(&debugger))) {
		std::wcout<<"Failed - SetManagedHandler";
		corDebug->Release();
		return 0;
	}

	STARTUPINFO info = {sizeof(STARTUPINFO), 0};
	PROCESS_INFORMATION pi;
	ICorDebugProcess* debugProcess;
	if(FAILED(corDebug->CreateProcessW(processName.c_str(), &commandLine[0], 0, 0, FALSE, 0, 0, 0, &info, &pi, DEBUG_NO_SPECIAL_OPTIONS, &debugProcess))) {
		std::wcout<<"Failed - CreateProcessW";
		corDebug->Release();
		return 0;
	}
	debugger.WaitForDebuggingToFinish();
	corDebug->Terminate();
	corDebug->Release();
	return 0;
}
