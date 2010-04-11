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
#pragma once

#include "Handle.h"

#define CONTINUE_IMPL(p) { p->Continue(FALSE); return S_OK; }

namespace SlimGen
{
	class Debugger : public ICorDebugManagedCallback, public ICorDebugManagedCallback2
	{
	public:
		Debugger() : debug(CreateEvent(0, 0, FALSE, 0)) 
		{
		}

		ULONG STDMETHODCALLTYPE AddRef()
		{
			return InterlockedIncrement(reinterpret_cast<LONG*>(&refCount));
		}

		ULONG STDMETHODCALLTYPE Release()
		{
			return InterlockedDecrement(reinterpret_cast<LONG*>(&refCount));
		}

		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject)
		{
			if(riid == IID_ICorDebugManagedCallback || riid == IID_IUnknown)
				*ppvObject = static_cast<ICorDebugManagedCallback*>(this);
			else if(riid == IID_ICorDebugManagedCallback2)
				*ppvObject = static_cast<ICorDebugManagedCallback2*>(this);
			else
			{
				*ppvObject = 0;
				return E_NOINTERFACE;
			}

			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE ExitProcess(ICorDebugProcess*)
		{
			SetEvent(debug);
			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE DebuggerError(ICorDebugProcess*, HRESULT, DWORD) 
		{ 
			return S_OK; 
		}

		void WaitForDebuggingToFinish()
		{
			WaitForSingleObject(debug, INFINITE);
		}

		// ** DEFAULT IMPLEMENTATIONS ** //

		HRESULT STDMETHODCALLTYPE Breakpoint( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugBreakpoint*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE StepComplete( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugStepper*,
			CorDebugStepReason) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE Break( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*) CONTINUE_IMPL(pAppDomain);;

		HRESULT STDMETHODCALLTYPE Exception( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			BOOL) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE EvalComplete( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugEval*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE EvalException( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugEval*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE CreateProcess( 
			ICorDebugProcess *pProcess) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE CreateThread( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE ExitThread( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LoadModule( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugModule*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE UnloadModule( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugModule*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LoadClass( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugClass*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE UnloadClass( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugClass*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LogMessage( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			LONG,
			WCHAR*,
			WCHAR*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LogSwitch( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			LONG,
			ULONG,
			WCHAR*,
			WCHAR*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE CreateAppDomain( 
			ICorDebugProcess*,
			ICorDebugAppDomain *pAppDomain) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE ExitAppDomain( 
			ICorDebugProcess*,
			ICorDebugAppDomain *pAppDomain) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LoadAssembly( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugAssembly*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE UnloadAssembly( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugAssembly*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE ControlCTrap( 
			ICorDebugProcess *pProcess) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE NameChange( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE UpdateModuleSymbols( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugModule*,
			IStream*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE EditAndContinueRemap( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugFunction*,
			BOOL) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE BreakpointSetError( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugBreakpoint*,
			DWORD) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE FunctionRemapOpportunity( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugFunction*,
			ICorDebugFunction*,
			ULONG32) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE CreateConnection( 
			ICorDebugProcess *pProcess,
			CONNID,
			WCHAR*) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE ChangeConnection( 
			ICorDebugProcess *pProcess,
			CONNID) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE DestroyConnection( 
			ICorDebugProcess *pProcess,
			CONNID) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE Exception( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugFrame*,
			ULONG32,
			CorDebugExceptionCallbackType,
			DWORD) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE ExceptionUnwind( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			CorDebugExceptionUnwindCallbackType,
			DWORD) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE FunctionRemapComplete( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread*,
			ICorDebugFunction*) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE MDANotification( 
			ICorDebugController *pController,
			ICorDebugThread*,
			ICorDebugMDA*) CONTINUE_IMPL(pController);

	private:
		Handle debug;
		ULONG refCount;
	};
}