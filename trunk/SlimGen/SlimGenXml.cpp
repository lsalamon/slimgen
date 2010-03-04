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
#include "slimgenxml.h"
#include "tinyxml.h"

namespace SlimGen {
	void ParseAssemblies(SlimGenConfig& config, TiXmlElement* rootNode);
	void ParsePlatforms(AssemblyNode& assembly, TiXmlElement* rootNode);
	void ParseMethods(PlatformNode& platform, TiXmlElement* rootNode);
	void ParseInstructionSets(MethodNode& method, TiXmlElement* rootNode);

	SlimGenConfig LoadConfigurationFile(std::string const& filename) {
		SlimGenConfig slimGenConfig;

		TiXmlDocument configDoc(filename);
		configDoc.LoadFile();

		TiXmlElement* root = configDoc.FirstChildElement("slimGen");
		if(!root)
			throw std::runtime_error("Invalid XML configuration file: Expected root element 'slimGen'.");

		ParseAssemblies(slimGenConfig, root);

		return slimGenConfig;
	}

	void ParseAssemblies(SlimGenConfig& config, TiXmlElement* rootNode) {
		TiXmlElement* assembly = rootNode->FirstChildElement("assembly");
		while(assembly) {
			AssemblyNode assemblyNode;

			std::string name = assembly->Attribute("name");
			if(name.empty())
				throw std::runtime_error("Invalid XML configuration file: Expected assembly attribute 'name'.");
			assemblyNode.Name = std::wstring(name.begin(), name.end());

			ParsePlatforms(assemblyNode, assembly);

			config.Assemblies.push_back(assemblyNode);

			assembly = assembly->NextSiblingElement("assembly");
		}
	}

	void ParsePlatforms(AssemblyNode& assembly, TiXmlElement* rootNode) {
		TiXmlElement* platform = rootNode->FirstChildElement("platform");

		while(platform) {
			PlatformNode platformNode;

			std::string name = platform->Attribute("name");
			if(name.empty() || (name != "x86" && name != "x64"))
				throw std::runtime_error("Invalid XML configuration file: Expected platform attribute 'name' with value of either 'x86' or 'x64'.");
			platformNode.Name = std::wstring(name.begin(), name.end());

			ParseMethods(platformNode, platform);

			assembly.Platforms.push_back(platformNode);

			platform = platform->NextSiblingElement("platform");
		}
	}

	void ParseMethods(PlatformNode& platform, TiXmlElement* rootNode) {
		TiXmlElement* method = rootNode->FirstChildElement("method");

		while(method) {
			MethodNode methodNode;

			std::string name = method->Attribute("name");
			if(name.empty())
				throw std::runtime_error("Invalid XML configuration file: Expected method attribute 'name'.");
			methodNode.Name = std::wstring(name.begin(), name.end());

			ParseInstructionSets(methodNode, method);

			platform.Methods.push_back(methodNode);

			method = method->NextSiblingElement("method");
		}
	}

	void ParseInstructionSets(MethodNode& method, TiXmlElement* rootNode) {
		TiXmlElement* instructionSet = rootNode->FirstChildElement("instructionSet");

		while(instructionSet) {
			InstructionSetNode instructionSetNode;

			std::string value = instructionSet->Attribute("name");
			if(value.empty())
				throw std::runtime_error("Invalid XML configuration file: Expected instructionSet attribute 'name'.");
			instructionSetNode.Name = std::wstring(value.begin(), value.end());

			value = instructionSet->Attribute("bin");
			if(value.empty())
				throw std::runtime_error("Invalid XML configuration file: Expected instructionSet attribute 'bin'.");
			instructionSetNode.BinFilename = std::wstring(value.begin(), value.end());

			method.InstructionSets.push_back(instructionSetNode);

			instructionSet = instructionSet->NextSiblingElement("instructionSet");
		}
	}
}