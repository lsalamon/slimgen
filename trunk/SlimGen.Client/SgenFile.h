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

namespace PlatformSpecifier {
	enum Specifier : DWORD {
		X86,
		X64
	};
}

namespace InstructionSetSpecifier {
	enum Specifier : DWORD {
		Default,
		MMX,
		SSE,
		SSE2,
		SSE3,
		SSSE3,
		SSE41,
		SSE42
	};
}

static const int SGENFileSignature = 0x4E45753;
struct SgenChunkInfo {
	DWORD Length;
	InstructionSetSpecifier::Specifier InstructionSet;
	std::vector<BYTE> Data; //Length - 8 in size
};

struct SgenMethod {
	DWORD ChunkCount;
	DWORD MethodNameLength;
	std::wstring MethodName; //MethodNameLength in size
	DWORD MethodToken;
	std::vector<SgenChunkInfo> Chunks;
};

struct SgenPlatform {
	DWORD MethodCount;
	PlatformSpecifier::Specifier Platform;
	std::vector<SgenMethod> Methods;
};

struct SgenFile {
	DWORD Signature;
	DWORD PlatformCount;
	std::vector<SgenPlatform> Platforms;
};

void LoadSgen(std::wstring sgenFilename, SgenFile& sgenFile);
void GetMethodsForPlatformInstructionSet(PlatformSpecifier::Specifier platform, InstructionSetSpecifier::Specifier instructionSet, SgenFile const& file, std::vector<SgenMethod>& methods);