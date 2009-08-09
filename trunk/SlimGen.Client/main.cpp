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

int wmain(int argc, wchar_t** argv)
{
	if(argc != 3) {
		std::cout<<"Usage: SlimGen.Client <Assembly> <Sgen Package>";
		return 0;
	}

	std::pair<std::wstring, std::vector<SlimGen::MethodNativeBlocks>> info;
	try
	{
		info = SlimGen::GetNativeImageInformation(argv[1]);
	} 
	catch(std::runtime_error& error)
	{
		std::cout<<"Unhandled exception encountered: "<<error.what()<<std::endl;
		return -1;
	}

	SgenFile sgenFile;
	LoadSgen(argv[2], sgenFile);

	std::vector<SgenMethod> methods;
	GetMethodsForPlatformInstructionSet(PlatformSpecifier::X86, InstructionSetSpecifier::SSE2, sgenFile, methods);

	std::vector<MethodDescriptor> descriptors;
	for each(const SgenMethod &method in methods)
	{
		std::vector<SlimGen::MethodNativeBlocks>::const_iterator block = info.second.begin();
		for(; block != info.second.end(); ++block)
		{
			if(block->Signature == method.MethodSignature)
				break;
		}

		if(block == info.second.end())
			throw std::runtime_error("fuck off");

		for (int i = 0; i < block->CodeChunks.size(); i++)
		{
			MethodDescriptor descriptor;
			descriptor.BaseAddress = block->CodeChunks.at(i).startAddr;
			descriptor.Length = method.Chunks.at(i).Length;
			descriptor.Data = &method.Chunks.at(i).Data[0];

			descriptors.push_back(descriptor);
		}
	}

	InjectNativeCode(info.first, descriptors);
}