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
#include <cor.h>
#include <cordebug.h>
#include <MSCorEE.h>
#include <atlbase.h>

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "SigFormat.h"
#include "Debugger.h"
#include "Handle.h"

namespace SlimGen {
	class RuntimeMethodReplacer {
	public:
		RuntimeMethodReplacer() {
			debuggerCallback.SetAssemblyHandler(boost::bind(boost::mem_fn(&RuntimeMethodReplacer::VisitAssemblyHandler), this, _1, _2));
			debuggerCallback.SetFunctionHandler(boost::bind(boost::mem_fn(&RuntimeMethodReplacer::VisitFunctionHandler), this, _1, _2));
			debuggerCallback.SetTypeHandler(boost::bind(boost::mem_fn(&RuntimeMethodReplacer::VisitTypeHandler), this, _1));
		}

		void Run(std::wstring const& process, std::wstring& arguments) {
			if(FAILED(CoInitialize(0)))
				throw std::runtime_error("Unable to initialize COM.");

			std::wstring version = GetRuntimeVersionFromFile(process);

			CComPtr<ICorDebug> corDebug;
			if(FAILED(CreateDebuggingInterfaceFromVersion(CorDebugLatestVersion, version.c_str(), reinterpret_cast<IUnknown**>(&corDebug.p))))
				throw std::runtime_error("Unable to create debugging interface from version.");

			if(FAILED(corDebug->Initialize()))
				throw std::runtime_error("Unable to initialize debugging interface.");

			if(FAILED(corDebug->SetManagedHandler(&debuggerCallback)))
				throw std::runtime_error("Unable to set managed debugger callback.");

			STARTUPINFO si = { sizeof(STARTUPINFO), 0};
			PROCESS_INFORMATION pi;

			if(FAILED(corDebug->CreateProcess(process.c_str(), &arguments[0], 0, 0, FALSE, 0, 0, 0, &si, &pi, DEBUG_NO_SPECIAL_OPTIONS, &debugProcess.p)))
				throw std::runtime_error("Unable to create process for debugging.");

			debuggerCallback.WaitForDebuggingToFinish();
			corDebug->Terminate();

			CoUninitialize();
		}

		void AddAssembly(std::wstring const& assembly) { assemblies.push_back(assembly); }
		void AddSignature(std::wstring const& sig) { signatures.push_back(sig); }
		void AddSignatureInstructionSet(std::wstring const& sig, std::pair<std::wstring, std::wstring> const& instructionSet) {
			signatureToInstructionSets[sig].push_back(instructionSet);
		}

	private:
		bool VisitAssemblyHandler(ICorDebugAssembly* assembly, std::wstring const& name) {
			for(std::size_t i = 0; i < assemblies.size(); ++i) {
				if(name.find(assemblies[i]) != name.npos) {
					return true;
				}
			}
			return false;
		}

		void VisitFunctionHandler(ICorDebugFunction* function, std::wstring const& signature) {
			for(std::size_t i = 0; i < signatures.size(); ++i) {
				if(signature == signatures[i]) {
					CComPtr<ICorDebugCode> codePtr;
					function->GetNativeCode(&codePtr.p);
					CComQIPtr<ICorDebugCode2> code2Ptr(codePtr);
					CodeChunkInfo cci;
					ULONG32 len = 1;
					code2Ptr->GetCodeChunks(len, &len, &cci);

					std::vector<std::pair<std::wstring, std::wstring> >& instructionSets = signatureToInstructionSets[signature];
					for(std::size_t j = 0; j < instructionSets.size(); ++j) {
						Handle fileHandle(CreateFile(instructionSets[j].second.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0));
						DWORD len = GetFileSize(fileHandle, 0);
						if(len > cci.length)
							return;
						std::vector<BYTE> fileData(len);
						debugProcess->ReadMemory(cci.startAddr, len, &fileData.front(), &len); 
						ReadFile(fileHandle, &fileData.front(), len, &len, 0);
						debugProcess->WriteMemory(cci.startAddr, len, &fileData.front(), &len);
						fileData = std::vector<BYTE>(len);
						debugProcess->ReadMemory(cci.startAddr, len, &fileData.front(), &len); 
					}
				}
			}
		}

		bool VisitTypeHandler(std::wstring const& name) {
			return true;
		}
	private:
		std::vector<std::wstring> assemblies;
		std::vector<std::wstring> signatures;
		std::map<std::wstring, std::vector<std::pair<std::wstring, std::wstring> > > signatureToInstructionSets;
		Debugger debuggerCallback;
		CComPtr<ICorDebugProcess> debugProcess;
	};
}

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
