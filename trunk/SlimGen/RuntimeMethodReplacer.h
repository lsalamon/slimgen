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

#include "stdafx.h"

#include "SigFormat.h"
#include "Debugger.h"
#include "Handle.h"

namespace SlimGen {
	class RuntimeMethodReplacer {
	public:
		RuntimeMethodReplacer();

		void Run(std::wstring const& process, std::wstring& arguments) ;

		void AddAssembly(std::wstring const& assembly);
		void AddSignature(std::wstring const& sig);
		void AddSignatureInstructionSet(std::wstring const& sig, std::pair<std::wstring, std::wstring> const& instructionSet);

	private:
		bool VisitAssemblyHandler(ICorDebugAssembly* assembly, std::wstring const& name);
		void VisitFunctionHandler(ICorDebugFunction* function, std::wstring const& signature) ;
		bool VisitTypeHandler(std::wstring const& name) ;
		void VisitDoneProcessing(ICorDebugAppDomain* appDomain);
	private:
		Handle waitForSlimGen;
		std::vector<std::wstring> assemblies;
		std::vector<std::wstring> signatures;
		std::map<std::wstring, std::vector<std::pair<std::wstring, std::wstring> > > signatureToInstructionSets;
		Debugger debuggerCallback;
		CComPtr<ICorDebugProcess> debugProcess;
	};
}