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
#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_ATTRIBUTES
#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#include <atlbase.h>
#include <atlcom.h>
#include <atlwin.h>
#include <atltypes.h>
#include <atlctl.h>
#include <atlhost.h>

using namespace ATL;

[object, uuid("{38321A69-A0D5-4ab3-8D54-AD29F20CE976}"), helpstring("ISlimGenNamedObject Interface")]
__interface ISlimGenNamedObject : IUnknown {
	HRESULT GetName([out, size_is(*nameLen), length_is(*nameLen)] LPWSTR* name, [in, out] DWORD* nameLen);
};

[object, uuid("{AF78E859-56C9-4f30-B9F3-6109B5F9597A}"), helpstring("ISlimGenEnum Interface")]
__interface ISlimGenEnum : IUnknown {
	HRESULT Get([out, retval] ISlimGenNamedObject** object);
	HRESULT Next();
};

[object, uuid("{47CB0D63-925A-468e-9BA4-3C9CA9BE1132}"), helpstring("ISlimGenMethod Interface")]
__interface ISlimGenMethod : ISlimGenNamedObject {
	HRESULT ReplaceMethod([in, size_is(dataLen)] char const * data, [in] DWORD dataLen);
	HRESULT GetRVA([out, retval] char** address);
};

[object, uuid("{A3F9CC35-CA09-4f8b-AC85-1062733748CA}"), helpstring("ISlimGenAssembly Interface")]
__interface ISlimGenAssembly : ISlimGenNamedObject {
	HRESULT EnumNativeMethods([out, retval] ISlimGenEnum** enumerator);
};

[object, uuid("{75BCB7EA-ACCA-4d45-A2EB-B8A4432F4D68}"), helpstring("ISlimGenProcess Interface")]
__interface ISlimGenProcess : IUnknown {
	HRESULT EnumAssemblies([out, retval] ISlimGenAssembly** assemblies);
	HRESULT WaitForBreak([in] DWORD timeout);
};

[object, uuid("{1E5967CD-C618-4fbe-85D6-46BD21F5E9C1}"), helpstring("ISlimGen Interface")]
__interface ISlimGen : IUnknown {
	HRESULT Initialize();
	HRESULT CreateSlimGenProcess([in] LPCWSTR processName, [in] LPCWSTR arguments, [out, retval] ISlimGenProcess** process);
	HRESULT AttachToProcess([in] DWORD processId, [out, retval] ISlimGenProcess** process);
};

#ifdef SLIMGEN_EXPORTS
#define DLLMETHOD __declspec(dllexport)
#else
#define DLLMETHOD __declspec(dllimport)
#endif

HRESULT DLLMETHOD CreateSlimGen(ISlimGen** result);