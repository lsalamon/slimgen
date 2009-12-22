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

#pragma once

#ifdef _DEBUG
#define DEBUG_PRINT_ENTER //std::wcout<<"ENTERED: "<<__FUNCTION__<<std::endl;
#else
#define DEBUG_PRINT_ENTER
#endif

#define CONTINUE_IMPL(p) {\
	DEBUG_PRINT_ENTER\
	p->Continue(FALSE);\
	return S_OK;\
}

namespace SlimGen {
	class DebuggerImpl : public ICorDebugManagedCallback, public ICorDebugManagedCallback2 {
	public:
		DebuggerImpl() : debug(CreateEvent(0, 0, FALSE, 0)) {}
		ULONG STDMETHODCALLTYPE AddRef()  {
			return InterlockedIncrement(reinterpret_cast<LONG*>(&refCount));
		}

		ULONG STDMETHODCALLTYPE Release() {
			return InterlockedDecrement(reinterpret_cast<LONG*>(&refCount));
		}

		HRESULT STDMETHODCALLTYPE QueryInterface(
			REFIID riid,
			void **ppvObject) {
				if(riid == IID_ICorDebugManagedCallback || riid == IID_IUnknown)
					*ppvObject = static_cast<ICorDebugManagedCallback*>(this);
				else if(riid == IID_ICorDebugManagedCallback2)
					*ppvObject = static_cast<ICorDebugManagedCallback2*>(this);
				else {
					*ppvObject = 0;
					return E_NOINTERFACE;
				}

				return S_OK;
		}

		HRESULT STDMETHODCALLTYPE Breakpoint( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugBreakpoint *pBreakpoint) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE StepComplete( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugStepper *pStepper,
			CorDebugStepReason reason) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE Break( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *thread) CONTINUE_IMPL(pAppDomain);;

		HRESULT STDMETHODCALLTYPE Exception( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			BOOL unhandled) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE EvalComplete( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugEval *pEval) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE EvalException( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugEval *pEval) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE CreateProcess( 
			ICorDebugProcess *pProcess) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE ExitProcess( 
			ICorDebugProcess *pProcess) {
				DEBUG_PRINT_ENTER
					SetEvent(debug);
				//pProcess->Detach();
				return S_OK;
		}

		HRESULT STDMETHODCALLTYPE CreateThread( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *thread) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE ExitThread( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *thread) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LoadModule( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugModule *pModule) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE UnloadModule( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugModule *pModule) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LoadClass( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugClass *c) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE UnloadClass( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugClass *c) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE DebuggerError( 
			ICorDebugProcess *pProcess,
			HRESULT errorHR,
			DWORD errorCode) { std::wcout<<"ENTERED: "<<__FUNCTION__<<std::endl; return S_OK; }

		HRESULT STDMETHODCALLTYPE LogMessage( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			LONG lLevel,
			WCHAR *pLogSwitchName,
			WCHAR *pMessage) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LogSwitch( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			LONG lLevel,
			ULONG ulReason,
			WCHAR *pLogSwitchName,
			WCHAR *pParentName) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE CreateAppDomain( 
			ICorDebugProcess *pProcess,
			ICorDebugAppDomain *pAppDomain) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE ExitAppDomain( 
			ICorDebugProcess *pProcess,
			ICorDebugAppDomain *pAppDomain) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE LoadAssembly( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugAssembly *pAssembly) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE UnloadAssembly( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugAssembly *pAssembly) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE ControlCTrap( 
			ICorDebugProcess *pProcess) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE NameChange( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE UpdateModuleSymbols( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugModule *pModule,
			IStream *pSymbolStream) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE EditAndContinueRemap( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugFunction *pFunction,
			BOOL fAccurate) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE BreakpointSetError( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugBreakpoint *pBreakpoint,
			DWORD dwError) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE FunctionRemapOpportunity( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugFunction *pOldFunction,
			ICorDebugFunction *pNewFunction,
			ULONG32 oldILOffset) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE CreateConnection( 
			ICorDebugProcess *pProcess,
			CONNID dwConnectionId,
			WCHAR *pConnName) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE ChangeConnection( 
			ICorDebugProcess *pProcess,
			CONNID dwConnectionId) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE DestroyConnection( 
			ICorDebugProcess *pProcess,
			CONNID dwConnectionId) CONTINUE_IMPL(pProcess);

		HRESULT STDMETHODCALLTYPE Exception( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugFrame *pFrame,
			ULONG32 nOffset,
			CorDebugExceptionCallbackType dwEventType,
			DWORD dwFlags) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE ExceptionUnwind( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			CorDebugExceptionUnwindCallbackType dwEventType,
			DWORD dwFlags) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE FunctionRemapComplete( 
			ICorDebugAppDomain *pAppDomain,
			ICorDebugThread *pThread,
			ICorDebugFunction *pFunction) CONTINUE_IMPL(pAppDomain);

		HRESULT STDMETHODCALLTYPE MDANotification( 
			ICorDebugController *pController,
			ICorDebugThread *pThread,
			ICorDebugMDA *pMDA) CONTINUE_IMPL(pController);

		void WaitForDebuggingToFinish() {
			WaitForSingleObject (debug, INFINITE);
		}
	private:
		HANDLE debug;
		ULONG refCount;
	};
}