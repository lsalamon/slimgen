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