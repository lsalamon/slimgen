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

#include <Windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <cor.h>
#include <cordebug.h>
#include <vector>
#include <iostream>
#include <string>
#include <psapi.h>
#include <mscoree.h>
#include "..\DebuggerLib\Debugger.h"

#include <fstream>
#include <sstream>

void GenerateTemplateAsm(std::wstring const& methodName, std::wstring const& methodSignature, CORDB_ADDRESS rva, std::size_t length) {
	std::wofstream fout((methodName + L".asm").c_str());
	fout<<L";-------------------------------------------------------------------------------"<<std::endl
		<<L"; nasm -fbin -o"<<methodName
#ifdef _M_X64
		<<L".X64"
#else
		<<L".X32"
#endif
		<<" "<<methodName<<L".asm"<<std::endl
		<<L"; "<<methodName<<std::endl
		<<L"; RVA: 0x"<<std::hex<<rva<<std::endl
		<<L"; Length: "<<std::dec<<length<<std::endl
		<<L"; Calling convention is clr __fastcall:"<<std::endl
#ifdef _M_X64
		<<L";  X64: First four arguments in registers RCX, RDX, R8 and R9 the remainder are"<<std::endl
		<<L";       on the stack."<<std::endl
#else
		<<L";  X86: First two arguments in registers ECX and EDX the remainder are on the"<<std::endl
		<<L";       stack right to left."<<std::endl
#endif
		<<L";-------------------------------------------------------------------------------"<<std::endl
#ifdef _M_X64
		<<L"BITS        64"<<std::endl
#else
		<<L"BITS        32"<<std::endl
#endif
		<<L"ORG         0x"<<std::hex<<rva<<std::endl
		<<L"start:"<<std::endl
		<<L"            ret     4"<<std::endl
		<<L";-------------------------------------------------------------------------------"<<std::endl
		<<L"; Buffer out to the size of the original method: "<<std::endl
		<<L"; WARNING: DO NOT EXCEED THIS SIZE"<<std::endl
		<<L"            TIMES 0x"<<std::hex<<length<<L"-($-$$) DB 0xCC"<<std::endl
		<<L";==============================================================================="<<std::endl
		<<L"; WARNING: DO NOT REMOVE {"<<std::endl
		<<L";==============================================================================="<<std::endl
		<<L"%define methodName      '"<<methodName<<L"'"<<std::endl
		<<L"%define methodSignature '"<<methodSignature<<L"'"<<std::endl
		<<L";==============================================================================="<<std::endl
		<<L"; WARNING: DO NOT REMOVE }"<<std::endl
		<<L";==============================================================================="<<std::endl;
}

int wmain(int argc, wchar_t** argv) {
	if(argc < 2) {
		std::cout<<"Usage: tg.exe <AssemblyName>"<<std::endl
			<<"  AssemblyName: The full name of the appropriate assembly or path to the file."<<std::endl
			<<"Examples:"<<std::endl
			<<"  tg.exe \"SlimDX, Culture=en, PublicKeyToken=a5d015c7d5a0b012, Version=1.0.0.0\""<<std::endl
			<<"  tg.exe SlimDX.dll"<<std::endl;
		return 0;
	}

	std::pair<std::wstring, std::vector<SlimGen::MethodNativeBlocks>> info;
	try {
		info = SlimGen::GetNativeImageInformation(argv[1]);
	} catch(std::runtime_error& error) {
		std::cout<<"Unhandled exception encountered: "<<error.what()<<std::endl;
		return -1;
	}

	for(std::size_t i = 0; i < info.second.size(); ++i) {
		for(std::size_t j = 0; j < info.second[i].CodeChunks.size(); ++j) {
			std::wstringstream ss;
			ss<<info.second[i].MethodName;
			if(info.second[i].CodeChunks.size() > 1) {
				ss<<j;
			}
			GenerateTemplateAsm(ss.str(), info.second[i].Signature, info.second[i].CodeChunks[j].startAddr, info.second[i].CodeChunks[j].length);
		}
	}
}