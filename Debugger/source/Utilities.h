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

namespace SlimGen
{
	template<class T> std::wstring GetName(T* ptr)
    {
        ULONG32 nameLen = 0;
        ptr->GetName(nameLen, &nameLen, 0);

        std::wstring name(nameLen, 0);
        ptr->GetName(nameLen, &nameLen, &name[0]);

        return std::wstring(name.begin(), name.end() - 1);
    }

	std::wstring GetMethodNameFromDef( IMetaDataImport2* metadata, mdMethodDef methodDef);
	std::wstring GetTypeNameFromDef(IMetaDataImport2* metadata, mdTypeDef typeDef);
	std::wstring GetRuntimeVersion(int processId);

	class Handle
	{
	public:
		Handle() : handle(0) {}
		Handle(HANDLE handle) : handle(handle) {}

		~Handle() { if(handle) CloseHandle(handle); }

		operator HANDLE&() { return handle; }
		HANDLE* operator&() { return &handle; }
		void Reset(HANDLE newValue = 0) { handle = newValue; }

		bool IsInvalid() { return handle == 0 || handle == INVALID_HANDLE_VALUE; }

	private:
		Handle(const Handle&) {}
		void operator =(const Handle& other) const;
		HANDLE handle;
	};
}