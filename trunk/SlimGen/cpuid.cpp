/*
* Copyright (c) 2007-2010 SlimGen Group
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
