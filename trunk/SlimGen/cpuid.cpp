#include "stdafx.h"
#include <intrin.h>
#include <iostream>
#include "cpuid.h"

namespace SlimGen {
	CPUFeatureSupport GetMaxCPUFeatureSupported() {
		CPUFeatureSupport feature = {};
		int CPUInfo[4];
		__cpuid(CPUInfo, 1);
		if(CPUInfo[3] & (1 << 23))
			feature.MMX = true;
		if(CPUInfo[3] & 0x2000000)
			feature.SSE = true;
		if(CPUInfo[3] & 0x4000000)
			feature.SSE2 = true;
		if(CPUInfo[2] & 1)
			feature.SSE3 = true;
		if(CPUInfo[2] & (1 << 9))
			feature.SSSE3 = true;
		if(CPUInfo[2] & (1 << 19))
			feature.SSE41 = true;
		if(CPUInfo[2] & (1 << 20))
			feature.SSE42 = true;

		__cpuid(CPUInfo, 0x80000000);
		if(CPUInfo[0] >= 0x80000001) {
			__cpuid(CPUInfo, 0x80000001);
			if(CPUInfo[2] & (1 << 6))
				feature.SSE4A = true;
		}

		return feature;
	}

	bool CPUFeatureSupport::FromName(std::wstring const& name) {
		if(name == L"MMX")
			return MMX;
		if(name == L"SSE")
			return SSE;
		if(name == L"SSE2")
			return SSE2;
		if(name == L"SSE3")
			return SSE3;
		if(name == L"SSSE3")
			return SSSE3;
		if(name == L"SSE41")
			return SSE41;
		if(name == L"SSE42")
			return SSE42;
		if(name == L"SSE4A")
			return SSE4A;

		return false;
	}

	int ValueFromName(std::wstring const& name) {
		if(name == L"MMX")
			return 1;
		if(name == L"SSE")
			return 2;
		if(name == L"SSE2")
			return 3;
		if(name == L"SSE3")
			return 4;
		if(name == L"SSSE3")
			return 5;
		if(name == L"SSE41")
			return 6;
		if(name == L"SSE42")
			return 7;
		if(name == L"SSE4A")
			return 8;

		return 0;
	}
}
