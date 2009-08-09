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
#include <intrin.h>
class CpuId {
public:
	CpuId() {
		__cpuid(CPUInfo, 1);
	}

	bool HasMMXSupport() const {
		return (CPUInfo[3] & MMXSupportBit) != 0;
	}

	bool HasSSESupport() const {
		return (CPUInfo[3] & SSESupportBit) != 0;
	}

	bool HasSSE2Support() const {
		return (CPUInfo[3] & SSE2SupportBit) != 0;
	}

	bool HasSSE3Support() const {
		return (CPUInfo[2] & SSE3SupportBit) != 0;
	}

	bool HasSSSE3Support() const {
		return (CPUInfo[2] & SSSE3SupportBit) != 0;
	}

	bool HasSSE41Support() const {
		return (CPUInfo[2] & SSE41SupportBit) != 0;
	}

	bool HasSSE42Support() const {
		return (CPUInfo[2] & SSE42SupportBit) != 0;
	}

	InstructionSetSpecifier::Specifier GetBestInstructionSet() const {
		if(HasSSE42Support())
			return InstructionSetSpecifier::SSE42;
		if(HasSSE41Support())
			return InstructionSetSpecifier::SSE41;
		if(HasSSSE3Support())
			return InstructionSetSpecifier::SSSE3;
		if(HasSSE3Support())
			return InstructionSetSpecifier::SSE3;
		if(HasSSE2Support())
			return InstructionSetSpecifier::SSE2;
		if(HasSSESupport())
			return InstructionSetSpecifier::SSE;
		if(HasMMXSupport())
			return InstructionSetSpecifier::MMX;

		return InstructionSetSpecifier::Default;
	}
private:
	enum SupportBits {
		MMXSupportBit = 1 << 23,
		SSESupportBit = 1 << 25,
		SSE2SupportBit = 1 << 26,
		SSE3SupportBit = 1,
		SSSE3SupportBit = 1 << 9,
		SSE41SupportBit = 1 << 19,
		SSE42SupportBit = 1 << 20
	};
	int CPUInfo[4];
};

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

	CpuId cpuid;
#ifdef _M_X64
	GetMethodsForPlatformInstructionSet(PlatformSpecifier::X64, cpuid.GetBestInstructionSet(), sgenFile, methods);
#else
	GetMethodsForPlatformInstructionSet(PlatformSpecifier::X86, cpuid.GetBestInstructionSet(), sgenFile, methods);
#endif

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

		for (std::size_t i = 0; i < block->CodeChunks.size(); i++)
		{
			MethodDescriptor descriptor;
			if(block->CodeChunks.at(i).startAddr > 0xFFFFFFFF)
				throw std::runtime_error("Method offset is larger than size of DWORD.");
			descriptor.BaseAddress = static_cast<DWORD>(block->CodeChunks.at(i).startAddr);
			descriptor.Length = method.Chunks.at(i).Length;
			descriptor.Data = &method.Chunks.at(i).Data[0];

			descriptors.push_back(descriptor);
		}
	}

	InjectNativeCode(info.first, descriptors);
}