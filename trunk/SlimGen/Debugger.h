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
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "DebuggerImpl.h"

namespace SlimGen {
	class Debugger : public DebuggerImpl {
	public:
		HRESULT STDMETHODCALLTYPE CreateAppDomain( ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain );
		HRESULT STDMETHODCALLTYPE Break(ICorDebugAppDomain* appDomain, ICorDebugThread* thread);

		void SetAssemblyHandler(boost::function<bool (ICorDebugAssembly*, std::wstring const&)> const& handler) {
			visitAssemblyHandler = handler;
		}

		void SetModuleHandler(boost::function<bool (ICorDebugModule*, std::wstring const&)> const& handler) {
			visitModuleHandler = handler;
		}

		void SetTypeHandler(boost::function<bool (std::wstring const&)> const& handler) {
			visitTypeHandler = handler;
		}

		void SetFunctionHandler(boost::function<void (ICorDebugFunction* function, std::wstring const& signature)> const& handler) {
			visitFunctionHandler = handler;
		}
	private:
		std::wstring GetMethodNameFromDef( IMetaDataImport2* metadata, mdMethodDef methodDef);
		std::wstring GetTypeNameFromDef( IMetaDataImport2* metadata, mdTypeDef typeDef);

		boost::function<bool (ICorDebugAssembly*, std::wstring const&)> visitAssemblyHandler;
		boost::function<bool (ICorDebugModule*, std::wstring const&)> visitModuleHandler;
		boost::function<void (ICorDebugFunction* function, std::wstring const& signature)> visitFunctionHandler;
		boost::function<bool (std::wstring const&)> visitTypeHandler;

		std::vector<ICorDebugModule*> modules;
		std::vector<ICorDebugAssembly*> assemblies;
	};

	std::wstring GetRuntimeVersionFromFile(std::wstring const& filename);
}