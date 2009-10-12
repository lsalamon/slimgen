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

#include "SlimGen.h"
#include "SlimGenUnknown.h"

#include <cor.h>
#include <cordebug.h>
#include <mscoree.h>
#include <stdexcept>
#include "DebuggerImpl.h"
#include <string>

#include <vector>

#include "SlimGenImpl.h"
#include "SlimGenProcess.h"

[module(type=dll, name="SlimGenServer", uuid="{9D5DC86D-2C2E-41bc-954B-58B20A39393A}")]
[emitidl];

namespace SlimGen {
	SlimGen::SlimGen() : wasInitialized(false) {}

	void SlimGen::OnCleanup()  {
		if(debugger)
			debugger->Terminate ();
	}

	HRESULT SlimGen::Initialize() {
		try {
			
		} catch(...) {
			return E_FAIL;
		}

		wasInitialized = true;
		return S_OK;
	}

	HRESULT SlimGen::CreateSlimGenProcess(LPCWSTR processName, LPCWSTR arguments, ISlimGenProcess** process) {
		*process = 0;
		if(!wasInitialized)
			return E_FAIL;

		WCHAR version[256];
		DWORD bufLen = 256;

		std::size_t processNameLen = wcslen(processName);
		LPWSTR processNameTmp = new WCHAR[processNameLen];
		wcsncpy_s(processNameTmp, processNameLen, processName, processNameLen);

		HRESULT hr = GetRequestedRuntimeVersion(processNameTmp, version, bufLen, &bufLen);
		if(FAILED(hr)) {
			delete [] processNameTmp;
			return hr;
		}

		delete [] processNameTmp;

		CComPtr<ICorDebug> debugPtr;
		if(FAILED(hr = CreateDebuggingInterfaceFromVersion (CorDebugLatestVersion, version, reinterpret_cast<IUnknown**>(&debugPtr))))
			return hr;

		if(FAILED(hr = debugPtr->Initialize ()))
			return hr;

		if(FAILED(hr = debugPtr->SetManagedHandler (callback)))
			return hr;

		STARTUPINFO startInfo = {};
		startInfo.cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION pi = {};

		WCHAR commandLine[MAX_PATH];
		std::wstring commandLineStr = L"HostProcess.exe \"";
		commandLineStr += arguments;
		commandLineStr += L"\"";

		wcsncpy_s(commandLine, MAX_PATH, commandLineStr.c_str(), commandLineStr.size());

		CComPtr<ICorDebugProcess> processPtr;
		if(FAILED(hr = debugPtr->CreateProcess (processName, commandLine, 0, 0, FALSE, 0, 0, 0, &startInfo, &pi, DEBUG_NO_SPECIAL_OPTIONS, &processPtr)))
			return hr;

		debugger = debugPtr;

		try {
			ISlimGenProcess* proc = new SlimGenProcess(this, processPtr);
			*process = proc;
		} catch(std::bad_alloc&) {
			return E_OUTOFMEMORY;
		} catch(...) {
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT SlimGen::AttachToProcess(DWORD processId, ISlimGenProcess** process) {
		*process = 0;
		if(!wasInitialized)
			return E_FAIL;

		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
		if(processHandle == NULL)
			return E_FAIL;

		WCHAR version[256];
		DWORD bufLen = 256;
		HRESULT hr;

		if(FAILED(hr = GetVersionFromProcess(processHandle, version, bufLen, &bufLen))) {
			CloseHandle (processHandle);
			return hr;
		}

		CloseHandle(processHandle);

		CComPtr<ICorDebug> debugPtr;
		if(FAILED(hr = CreateDebuggingInterfaceFromVersion(CorDebugLatestVersion, version, reinterpret_cast<IUnknown**>(&debugPtr)))) {
			return hr;
		}

		if(FAILED(hr = debugPtr->Initialize()))
			return hr;

		if(FAILED(hr = debugPtr->SetManagedHandler(callback)))
			return hr;

		CComPtr<ICorDebugProcess> processPtr;
		if(FAILED(hr = debugPtr->DebugActiveProcess (processId, FALSE, &processPtr)))
			return hr;

		debugger = debugPtr;

		try {
			ISlimGenProcess* proc = new SlimGenProcess(this, processPtr);
			*process = proc;
		} catch(std::bad_alloc&) {
			return E_OUTOFMEMORY;
		} catch(...) {
			return E_FAIL;
		}

		return E_NOTIMPL;
	}
}

HRESULT CreateSlimGen(ISlimGen** result) {
	try {
		SlimGen::SlimGen* ptr = new SlimGen::SlimGen();
		*result = ptr;
	} catch(std::bad_alloc&) {
		return E_OUTOFMEMORY;
	} catch(...) {
		return E_FAIL;
	}

	return S_OK;
}