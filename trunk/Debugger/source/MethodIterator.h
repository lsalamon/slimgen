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

#include "Debugger.h"
#include "MethodInformation.h"

namespace SlimGen
{
	class MethodIterator : private Debugger
	{
	public:
		MethodIterator(std::vector<MethodInformation>& methods) : methods(methods) { }
		virtual ~MethodIterator() {}

		void Run(int processId, std::wstring const& runtimeVersion);

	protected:
		virtual void FoundMethod(ICorDebugFunction* function, MethodInformation& method) = 0;
		CComPtr<ICorDebugProcess> debugProcess;
	private:
		HRESULT STDMETHODCALLTYPE CreateAppDomain(ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain);
		HRESULT STDMETHODCALLTYPE Break(ICorDebugAppDomain* appDomain, ICorDebugThread* thread);

		bool VisitAssemblyHandler(ICorDebugAssembly* assembly, const std::wstring& name);
		void VisitFunctionHandler(ICorDebugFunction* function, const std::wstring& signature);

		std::vector<MethodInformation>& methods;

		Handle waitForSlimGen;
		
	};
}