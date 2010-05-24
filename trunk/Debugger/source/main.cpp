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
#include "MethodTemplateBuilder.h"

#include <windows.h>
#include <sstream>
#include <string>

void SetPrivilege(HANDLE token, std::wstring const& privilage) {
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

void ConfigureDebugPrivilages() {
	SlimGen::Handle token;
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token))
		throw std::runtime_error("Unable to open current process.");

	SetPrivilege(token, SE_DEBUG_NAME);
}

void DoRuntimeMethodInformation(long processId) {	
	std::wstring runtimeVersion;
	std::getline(std::wcin, runtimeVersion);

	std::vector<SlimGen::MethodInformation> methods;
	while (std::cin.peek() != '\n') {
		SlimGen::MethodInformation method;
		std::getline(std::wcin, method.Assembly);
		std::getline(std::wcin, method.Method);

		int chunks;
		std::cin >> chunks >> std::ws;
		method.CompiledData = std::vector<std::vector<char>>(chunks);

		for (int i = 0; i < chunks; i++) {
			int size;
			std::cin >> size >> std::ws;

			method.CompiledData[i] = std::vector<char>(size);
			std::cin.read(&method.CompiledData[i][0], size);
		}
		methods.push_back(method);
	}

	if (methods.size() == 0) {
		std::wcout<<L"No methods to replace."<<std::endl;
		return;
	}

	SlimGen::RuntimeMethodReplacer methodReplacer(methods);
	methodReplacer.Run(processId, runtimeVersion);

	bool succeeded = true;
	for (size_t i = 0; i < methods.size(); i++) {
		if (!methods[i].Replaced) {
			std::wcout << L"Method " << methods[i].Method << L" was not replaced."<<std::endl;
			succeeded = false;
		}
	}

	if(!succeeded)
		throw std::runtime_error("Unable to replace some methods. Check output for listing.");
}

void DoRuntimeMethodBuilder(long processId) {
	std::wstring runtimeVersion;
	std::getline(std::wcin, runtimeVersion);

	std::wstring outputDirectory;
	std::getline(std::wcin, outputDirectory);

	std::vector<SlimGen::MethodInformation> methods;
	while(std::cin.peek() != '\n') {
		SlimGen::MethodInformation method;
		std::getline(std::wcin, method.Assembly);
		std::getline(std::wcin, method.Method);

		methods.push_back(method);
	}

	if (methods.size() == 0) {
		std::wcout<<L"No methods to replace."<<std::endl;
		return;
	}

	SlimGen::MethodTemplateBuilder methodTemplateBuilder(methods);
	methodTemplateBuilder.Run(processId, runtimeVersion);
}

int main(int argc, char** argv)
{
	if(argc < 2) {
		std::cout<<"Expected at least one argument."<<std::endl;
		return -1;
	}

	long processId;
	if(!(std::stringstream(argv[1]) >> processId)) {
		std::wcout<<L"Expected process ID."<<std::endl;
	}

	try {
		if(argc > 2) {
			if(std::stringstream(argv[2]).str() == "builder") {
			}
		} else {
			DoRuntimeMethodInformation(processId);
		}
	} catch(std::runtime_error& error) {
		std::wcout<<error.what()<<std::endl;
	}
}