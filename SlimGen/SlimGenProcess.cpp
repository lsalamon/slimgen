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
#include <cor.h>
#include <cordebug.h>
#include <mscoree.h>

#include <vector>

#include "SlimGenUnknown.h"
#include "DebuggerImpl.h"
#include "SlimGenImpl.h"
#include "SlimGenProcess.h"

namespace SlimGen {
	SlimGenProcess::SlimGenProcess(CComPtr<SlimGen> slimGen, CComPtr<ICorDebugProcess> process) : slimGen(slimGen),
		process(process), callback(slimGen->GetCallback ()), debugger(slimGen->GetDebugger ()), debugBreak(CreateEvent(0, TRUE, FALSE, 0)) {
	}

	HRESULT SlimGenProcess::EnumAssemblies(ISlimGenAssembly** assemblies) {
		HRESULT hr;
		CComPtr<ICorDebugAppDomainEnum> appDomains;
		if(FAILED(hr = process->EnumerateAppDomains (&appDomains)))
			return hr;

		ULONG appDomainCount;
		CComPtr<ICorDebugAppDomain> appDomain;
		appDomains->Next (1, &appDomain, &appDomainCount);
		while(appDomainCount) {
			CComPtr<ICorDebugAssemblyEnum> assemblies;
			if(FAILED(hr = appDomain->EnumerateAssemblies (&assemblies)))
				return hr;

			ULONG assemblyCount;
			CComPtr<ICorDebugAssembly> assembly;
			assemblies->Next (1, &assembly, &assemblyCount);
			while(assemblyCount) {
				//ISlimGenAssembly
				assemblies->Next (1, &assembly, &assemblyCount);
			}
			appDomain.Release ();
			appDomains->Next (1, &appDomain, &appDomainCount);
		}

		return E_NOTIMPL;
	}

	HRESULT SlimGenProcess::WaitForBreak(DWORD timeout) {
		WaitForSingleObject (debugBreak, timeout);
		return S_OK;
	}

	void SlimGenProcess::SetBreak () {
		SetEvent (debugBreak);
	}
}