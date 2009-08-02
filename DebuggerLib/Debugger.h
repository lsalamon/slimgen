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

#include "DebuggerImpl.h"

namespace SlimGen {
	struct MethodNativeBlocks {
		CORDB_ADDRESS BaseAddress;
		std::wstring MethodName;
		std::vector<CodeChunkInfo> CodeChunks;
	};

	std::pair<std::wstring, std::vector<SlimGen::MethodNativeBlocks>> GetNativeImageInformation( wchar_t* assemblyName );

	class Debugger : public DebuggerImpl {
	public:
		Debugger(std::wstring assemblySimpleName);

		HRESULT STDMETHODCALLTYPE CreateAppDomain(ICorDebugProcess *pProcess, ICorDebugAppDomain *pAppDomain);
		HRESULT STDMETHODCALLTYPE Break(ICorDebugAppDomain *pAppDomain, ICorDebugThread *thread);

		std::vector<MethodNativeBlocks> const& GetNativeMethodBlocks() const;
		std::wstring const& GetNativeImagePath() const;
	private:
		void EnumerateAssemblies( ICorDebugAppDomain * pAppDomain );
		void EnumerateModules(CComPtr<ICorDebugAssembly> assembly);
		void EnumerateTypes( CComPtr<IMetaDataImport2> metadata, CComPtr<ICorDebugModule> module );
		void EnumerateMethods( CComPtr<IMetaDataImport2> metadata, mdTypeDef typeDef, CComPtr<ICorDebugModule> module, std::wstring const& typeName );
		std::wstring GetTypeNameFromDef( CComPtr<IMetaDataImport2> metadata, mdTypeDef typeDef );
		std::wstring GetMethodNameFromDef( CComPtr<IMetaDataImport2> metadata, mdMethodDef methodDef );
		bool HasAttribute(CComPtr<IMetaDataImport2> metadata, mdMethodDef methodDef);

		std::wstring assemblySimpleName;
		std::wstring nativeImageName;
		std::vector<MethodNativeBlocks> methodBlocks;
	};
}