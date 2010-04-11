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

#include <intrin.h>
#include "cpuid.h"

CPUInfo __stdcall cpuid(int InfoType)
{
	int results[4];
	__cpuid(results, InfoType);

	CPUInfo i;
	i.Part1 = results[0];
	i.Part2 = results[1];
	i.Part3 = results[2];
	i.Part4 = results[3];

	return i;
}

CPUInfo __stdcall cpuidex(int InfoType, int ECXValue)
{
	int results[4];
	__cpuidex(results, InfoType, ECXValue);

	CPUInfo i;
	i.Part1 = results[0];
	i.Part2 = results[1];
	i.Part3 = results[2];
	i.Part4 = results[3];

	return i;
}