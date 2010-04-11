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
#include "MethodReplacement.h"

int main(int argc, char** argv)
{
	if (argc != 2)
		return -1;

	long processId = 0;
	std::stringstream(argv[1]) >> processId;

	std::vector<SlimGen::MethodReplacement> methods;
	while (std::cin.peek() != '\n')
	{
		SlimGen::MethodReplacement method;
		std::getline(std::wcin, method.Assembly);
		std::getline(std::wcin, method.Method);

		int chunks;
		std::cin >> chunks;
		method.CompiledData = std::vector<std::vector<char>>(chunks);

		for (int i = 0; i < chunks; i++)
		{
			int size;
			std::cin >> size;
			method.CompiledData[i] = std::vector<char>(size);
			std::cin.read(&method.CompiledData[i][0], size);
		}

		methods.push_back(method);
	}
}