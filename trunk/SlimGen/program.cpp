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

#include "stdafx.h"

#include "RuntimeMethodReplacer.h"

#include <sstream>
#include "tinyxml.h"

int wmain(int argc, wchar_t** argv) {
	if(argc < 3)
		return 0;

	std::wstringstream ss;
	for(int argumentIndex = 3; argumentIndex < argc; ++argumentIndex) {
		ss<<argv[argumentIndex]<<" ";
	}

	std::wstring arguments = ss.str();
	std::wstring configFile = argv[1];
	std::wstring process = argv[2];

	SlimGen::RuntimeMethodReplacer rmr;

	std::string fileName(configFile.begin(), configFile.end());
	TiXmlDocument config(fileName);

	config.LoadFile();
	TiXmlHandle configHandle(&config);
	TiXmlHandle root = configHandle.FirstChildElement("slimGen");
	TiXmlElement* assembly = root.FirstChild("assembly").ToElement();

	for(; assembly; assembly = assembly->NextSiblingElement()) {
		std::string value = assembly->Attribute("name");
		rmr.AddAssembly(std::wstring(value.begin(), value.end()));

		TiXmlHandle assemblyHandle = assembly;
		TiXmlElement* platform = assembly->FirstChildElement("platform");
		for(; platform; platform = platform->NextSiblingElement()) {
			std::string platformName = platform->Attribute("name");
#ifndef _M_X64
			if(platformName == "x86") {
#else
			if(platformName == "x64") {
#endif
				TiXmlElement* method = platform->FirstChildElement("method");
				for(; method; method = method->NextSiblingElement()) {
					std::string signature = method->Attribute("name");
					rmr.AddSignature(std::wstring(signature.begin(), signature.end()));

					TiXmlElement* instructionSet = method->FirstChildElement("instructionSet");
					for(; instructionSet; instructionSet = instructionSet->NextSiblingElement()) {
						std::string instructionSetName = instructionSet->Attribute("name");
						std::string bin = instructionSet->Attribute("bin");
						rmr.AddSignatureInstructionSet(std::wstring(signature.begin(), signature.end()), std::make_pair(std::wstring(instructionSetName.begin(), instructionSetName.end()), std::wstring(bin.begin(), bin.end())));
					}
				}
			}
		}
	}
	
	rmr.Run(process, arguments);
	return 0;
}
