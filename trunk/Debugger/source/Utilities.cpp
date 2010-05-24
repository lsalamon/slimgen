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
#include "stdafx.h"

#include "RuntimeMethodReplacer.h"
#include "SigFormat.h"

namespace SlimGen {
		std::wstring GetMethodNameFromDef( IMetaDataImport2* metadata, mdMethodDef methodDef)
    {
        ULONG methodNameLength;
        PCCOR_SIGNATURE signature;
        ULONG signatureLength;
        metadata->GetMethodProps(methodDef, 0, 0, 0, &methodNameLength, 0, 0, 0, 0, 0);

        std::wstring methodName(methodNameLength, 0);
        std::wstring signatureStr;
        metadata->GetMethodProps(methodDef, 0, &methodName[0], methodNameLength, &methodNameLength, 0, &signature, &signatureLength, 0, 0);

        wchar_t sigStr[2048];
        SigFormat formatter(sigStr, 2048, methodDef, metadata, metadata);
        formatter.Parse(static_cast<const sig_byte*>(signature), signatureLength);
        signatureStr = sigStr;

        return methodName.substr(0, methodName.length() - 1) + signatureStr;
    }

    std::wstring GetTypeNameFromDef(IMetaDataImport2* metadata, mdTypeDef typeDef)
    {
        ULONG typeNameLength;
        metadata->GetTypeDefProps(typeDef, 0, 0, &typeNameLength, 0, 0);

        std::wstring typeName(typeNameLength, 0);
        metadata->GetTypeDefProps(typeDef, &typeName[0], typeNameLength, &typeNameLength, 0, 0);

        return std::wstring(typeName.begin(), typeName.end() - 1);
    }

    std::wstring GetRuntimeVersion(int processId)
    {
        Handle handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
        if (handle.IsInvalid())
            throw std::runtime_error("Unable to open process.");

        std::wstringstream wss;
        wss<<std::hex<<handle<<std::endl<<processId;

        DWORD length;
        if (FAILED(GetVersionFromProcess(handle, NULL, 0, &length)))
            throw std::runtime_error("Unable to get version length from process.");

        std::wstring version(length, 0);
        if (FAILED(GetVersionFromProcess(handle, &version[0], length, &length)))
            throw std::runtime_error("Unable to get version from process.");

        return version;
    }
}