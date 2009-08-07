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
#include "Injection.h"
#include "SgenFile.h"
#include "..\DebuggerLib\Debugger.h"

int wmain(int argc, wchar_t** argv) {
	if(argc != 3) {
		std::cout<<"Usage: SlimGen.Client <Assembly> <Sgen Package>";
		return 0;
	}

	std::pair<std::wstring, std::vector<SlimGen::MethodNativeBlocks>> info;
	try {
		info = SlimGen::GetNativeImageInformation(argv[1]);
	} catch(std::runtime_error& error) {
		std::cout<<"Unhandled exception encountered: "<<error.what()<<std::endl;
		return -1;
	}

	for each(SlimGen::MethodNativeBlocks const& block in info.second) {

	}
}