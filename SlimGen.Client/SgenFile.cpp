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
			method.MethodName = std::wstring(method.MethodNameLength / sizeof(wchar_t), 0);
			ReadFile(file, &method.MethodName[0], method.MethodNameLength, &bytesRead, 0);
			ReadFile(file, &method.MethodToken, sizeof(DWORD), &bytesRead, 0);

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

		SgenMethod newMethod;
		newMethod.ChunkCount = 1;
		newMethod.Chunks.push_back(*best);
		newMethod.MethodName = method.MethodName;
		newMethod.MethodNameLength = method.MethodNameLength;
		newMethod.MethodToken = method.MethodToken;
		methods.push_back(newMethod);
	}
}