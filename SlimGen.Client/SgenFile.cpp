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

#include <windows.h>
#include <vector>
#include <string>
#include "Injection.h"
#include "SgenFile.h"

void LoadSgen(std::wstring sgenFilename, SgenFile& sgenFile) {
	ScopedHandle file = CreateFile(sgenFilename.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if(file == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Unable to open file.");

	DWORD bytesRead;
	ReadFile(file, &sgenFile.Signature, sizeof(DWORD), &bytesRead, 0);
	if(sgenFile.Signature != SGENFileSignature)
		throw std::runtime_error("Invalid SGEN file.");

	ReadFile(file, &sgenFile.PlatformCount, sizeof(DWORD), &bytesRead, 0);
	for(DWORD platformIndex = 0; platformIndex < sgenFile.PlatformCount; ++platformIndex) {
		SgenPlatform platform;
		ReadFile(file, &platform.MethodCount, sizeof(DWORD), &bytesRead, 0);
		ReadFile(file, &platform.Platform, sizeof(DWORD), &bytesRead, 0);
		for(DWORD methodIndex = 0; methodIndex < platform.MethodCount; ++methodIndex) {
			SgenMethod method;
			ReadFile(file, &method.ChunkCount, sizeof(DWORD), &bytesRead, 0);
			ReadFile(file, &method.MethodNameLength, sizeof(DWORD), &bytesRead, 0);
			ReadFile(file, &method.MethodSignatureLength, sizeof(DWORD), &bytesRead, 0);
			method.MethodName = std::wstring(method.MethodNameLength / sizeof(wchar_t), 0);
			method.MethodSignature = std::wstring(method.MethodSignatureLength / sizeof(wchar_t), 0);
			ReadFile(file, &method.MethodName[0], method.MethodNameLength, &bytesRead, 0);
			ReadFile(file, &method.MethodSignature[0], method.MethodSignatureLength, &bytesRead, 0);

			for(DWORD chunkIndex = 0; chunkIndex < method.ChunkCount; ++chunkIndex) {
				SgenChunkInfo chunk;
				ReadFile(file, &chunk.Length, sizeof(DWORD), &bytesRead, 0);
				ReadFile(file, &chunk.InstructionSet, sizeof(DWORD), &bytesRead, 0);
				chunk.Data.resize(chunk.Length);
				ReadFile(file, &chunk.Data[0], chunk.Length, &bytesRead, 0);

				method.Chunks.push_back(chunk);
			}

			platform.Methods.push_back(method);
		}
		sgenFile.Platforms.push_back(platform);
	}
}

void GetMethodsForPlatformInstructionSet(PlatformSpecifier::Specifier platform, InstructionSetSpecifier::Specifier instructionSet, SgenFile const& file, std::vector<SgenMethod>& methods) {
	std::vector<SgenPlatform>::const_iterator i = file.Platforms.begin();
	for(; i != file.Platforms.end(); ++i) {
		if(i->Platform == platform) {
			break;
		}
	}

	if(i == file.Platforms.end())
		throw std::runtime_error("No such platform available");

	for each(SgenMethod const& method in i->Methods) {
		SgenChunkInfo const* best = 0;
		for each(SgenChunkInfo const& chunk in method.Chunks) {
			if(chunk.InstructionSet <= instructionSet && (!best || chunk.InstructionSet > best->InstructionSet))
				best = &chunk;
		}

		if(!best)
			break;

		SgenMethod newMethod;
		newMethod.ChunkCount = 1;
		newMethod.Chunks.push_back(*best);
		newMethod.MethodName = method.MethodName;
		newMethod.MethodNameLength = method.MethodNameLength;
		newMethod.MethodSignatureLength = method.MethodSignatureLength;
		newMethod.MethodSignature = method.MethodSignature;
		methods.push_back(newMethod);
	}
}