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
#include "SlimGenXml.h"
#include "cpuid.h"
#include <iostream>

int main(int argc, char** argv) {
	if(argc < 2)
		return 0;

	std::string handleStr = argv[1];
	std::string configFile = argv[2];


	SlimGen::CPUFeatureSupport featureSupport = SlimGen::GetMaxCPUFeatureSupported();
	SlimGen::SlimGenConfig config = SlimGen::LoadConfigurationFile(configFile);
	
	for(std::size_t i = 0; i < config.Assemblies.size(); ++i) {
		std::wcout<<config.Assemblies[i].Name<<std::endl;
		for(std::size_t j = 0; j < config.Assemblies[i].Platforms.size(); ++j) {
			std::wcout<<L"  "<<config.Assemblies[i].Platforms[j].Name<<std::endl;
			for(std::size_t k = 0; k < config.Assemblies[i].Platforms[j].Methods.size(); ++k) {
				std::wcout<<L"    "<<config.Assemblies[i].Platforms[j].Methods[k].Name<<std::endl;
				std::vector<SlimGen::InstructionSetNode>& instructionSets = config.Assemblies[i].Platforms[j].Methods[k].InstructionSets;
				SlimGen::InstructionSetNode* best = 0;
				for(std::vector<SlimGen::InstructionSetNode>::iterator l = instructionSets.begin(); l != instructionSets.end(); ++l) {
					if(!best) {
						if(featureSupport.FromName(l->Name))
							best = &(*l);
					} else {
						if(SlimGen::ValueFromName(best->Name) < SlimGen::ValueFromName(l->Name) && featureSupport.FromName(l->Name))
							best = &(*l);
					}
				}
				if(best) {
					std::wcout<<L"      "<<best->Name<<L" : "<<best->BinFilename<<std::endl;
				}
			}
		}
	}
	return 0;
}