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

#include "Injection.h"

static const int SGENFileSignature = 0x4E45753;
struct ChunkHeader {
	DWORD Length;
	DWORD InstructionSet;
	std::vector<BYTE> Data; //Length - 8 in size
};

struct MethodHeader {
	DWORD ChunkCount;
	DWORD MethodNameLength;
	std::wstring MethodName; //MethodNameLength in size
	DWORD MethodToken;
	std::vector<ChunkHeader> Chunks;
};

struct PlatformHeader {
	DWORD MethodCount;
	DWORD Platform;
	std::vector<MethodHeader> Methods;
};

struct FileHeader {
	DWORD Signature;
	DWORD PlatformCount;
	std::vector<PlatformHeader> Platforms;
};

void LoadSgen(std::wstring sgenFilename) {
	ScopedHandle file = CreateFile(sgenFilename.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if(file == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Unable to open file.");

	FileHeader fileHeader = {};
	DWORD bytesRead;
	ReadFile(file, &fileHeader.Signature, sizeof(DWORD), &bytesRead, 0);
	if(fileHeader.Signature != SGENFileSignature)
		throw std::runtime_error("Invalid SGEN file.");

	ReadFile(file, &fileHeader.PlatformCount, sizeof(DWORD), &bytesRead, 0);
	for(DWORD platformIndex = 0; platformIndex < fileHeader.PlatformCount; ++platformIndex) {
		PlatformHeader platform;
		ReadFile(file, &platform.MethodCount, sizeof(DWORD), &bytesRead, 0);
		ReadFile(file, &platform.Platform, sizeof(DWORD), &bytesRead, 0);
		for(DWORD methodIndex = 0; methodIndex < platform.MethodCount; ++methodIndex) {
			MethodHeader method;
			ReadFile(file, &method.ChunkCount, sizeof(DWORD), &bytesRead, 0);
			ReadFile(file, &method.MethodNameLength, sizeof(DWORD), &bytesRead, 0);
			method.MethodName = std::wstring(method.MethodNameLength / sizeof(wchar_t), 0);
			ReadFile(file, &method.MethodName[0], method.MethodNameLength, &bytesRead, 0);
			ReadFile(file, &method.MethodToken, sizeof(DWORD), &bytesRead, 0);

			for(DWORD chunkIndex = 0; chunkIndex < method.ChunkCount; ++chunkIndex) {
				ChunkHeader chunk;
				ReadFile(file, &chunk.Length, sizeof(DWORD), &bytesRead, 0);
				ReadFile(file, &chunk.InstructionSet, sizeof(DWORD), &bytesRead, 0);
				chunk.Data.resize(chunk.Length);
				ReadFile(file, &chunk.Data[0], chunk.Length, &bytesRead, 0);

				method.Chunks.push_back(chunk);
			}

			platform.Methods.push_back(method);
		}
		fileHeader.Platforms.push_back(platform);
	}
}

int main()
{
}