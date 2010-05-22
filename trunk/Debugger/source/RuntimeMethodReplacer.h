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
#include "MethodReplacement.h"

namespace SlimGen
{
	class RuntimeMethodReplacer : private Debugger
	{
	public:
		RuntimeMethodReplacer(const std::vector<MethodReplacement>& methods) : methods(methods) { }

		void Run(int processId, std::wstring const& runtimeVersion);

	private:
		HRESULT STDMETHODCALLTYPE CreateAppDomain(ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain);
		HRESULT STDMETHODCALLTYPE Break(ICorDebugAppDomain* appDomain, ICorDebugThread* thread);

		std::wstring GetMethodNameFromDef( IMetaDataImport2* metadata, mdMethodDef methodDef);
		std::wstring GetTypeNameFromDef(IMetaDataImport2* metadata, mdTypeDef typeDef);

		void ReplaceMethod(ICorDebugFunction* function, MethodReplacement method);
		bool VisitAssemblyHandler(ICorDebugAssembly* assembly, const std::wstring& name);
		void VisitFunctionHandler(ICorDebugFunction* function, const std::wstring& signature);

		const std::vector<MethodReplacement>& methods;

		Handle waitForSlimGen;
		CComPtr<ICorDebugProcess> debugProcess;
	};

	std::wstring GetRuntimeVersion(int processId);
}