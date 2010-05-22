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
#include <windows.h>
#include <sstream>
#include <string>

void SetPrivilege(HANDLE token, std::wstring privilage) {
    LUID priv;
    LookupPrivilegeValue(L"", privilage.c_str(), &priv);
    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = priv;
    tp.Privileges[0].Attributes = 0;
    TOKEN_PRIVILEGES prev;
    DWORD prevLen;

    if(!AdjustTokenPrivileges(token, FALSE, &tp, sizeof(prev), &prev, &prevLen))
        throw std::runtime_error("Unable to view token privileges.");

    prev.PrivilegeCount = 1;
    prev.Privileges[0].Luid = priv;
    prev.Privileges[0].Attributes = prev.Privileges[0].Attributes | SE_PRIVILEGE_ENABLED;

    if(!AdjustTokenPrivileges(token, FALSE, &prev, prevLen, &tp, &prevLen))
        throw std::runtime_error("Unable to set token privileges.");
}

int main(int argc, char** argv)
{
    std::wstringstream wss;
	std::cout << "TraceB" << std::endl;

	if (argc != 2)
		return -1;

	long processId = 0;
	std::stringstream(argv[1]) >> processId;

    std::wstring runtimeVersion;
    std::getline(std::wcin, runtimeVersion);

	std::vector<SlimGen::MethodReplacement> methods;
	while (std::cin.peek() != '\n')
	{
		SlimGen::MethodReplacement method;
		std::getline(std::wcin, method.Assembly);
		std::getline(std::wcin, method.Method);

		int chunks;
        std::cin >> chunks >> std::ws;
		std::cout << chunks;
		method.CompiledData = std::vector<std::vector<char>>(chunks);

		for (int i = 0; i < chunks; i++)
		{
			int size;
            std::cin >> size >> std::ws;
			std::cout << size;
            
			method.CompiledData[i] = std::vector<char>(size);
			std::cin.read(&method.CompiledData[i][0], size);
		}

        
		methods.push_back(method);
	}

	

	std::cout << "TraceA" << std::endl;

	if (methods.size() == 0)
	{
		std::cout << "No methods to replace." << std::endl;
		return -2;
	}

	std::cout << "Trace1" << std::endl;

    ///////////////////////////////////////////////////////////////////////////
    HANDLE token;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);
    try {
        SetPrivilege(token, L"SeDebugPrivilege");
    } catch(std::runtime_error& exp) {
        MessageBoxA(0, exp.what(), "Test", MB_OK);
    }
    CloseHandle(token);
    ///////////////////////////////////////////////////////////////////////////

	try
	{
		SlimGen::RuntimeMethodReplacer methodReplacer(methods);
		methodReplacer.Run(processId, runtimeVersion);

		std::cout << "Trace2" << std::endl;
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what();
        MessageBoxA(0, e.what(), "Test", MB_OK);
		return -3;
	}

	std::cout << "Trace3" << std::endl;

	bool succeeded = true;
	for (size_t i = 0; i < methods.size(); i++)
	{
		if (!methods[i].Replaced)
		{
			std::wcout << "Method " << methods[i].Method << " was not replaced.";
			succeeded = false;
		}
	}

	std::cout << "Trace4" << std::endl;

	return succeeded ? 0 : -4;
}