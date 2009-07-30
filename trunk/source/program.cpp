#include "stdafx.h"
#include "Debugger\Debugger.h"

#include <fstream>

int wmain(int argc, wchar_t** argv) {
	if(argc < 3) {
		std::cout<<"Usage: tg.exe <AssemblyName> <OutputName>"<<std::endl
			<<"  AssemblyName: The full name of the appropriate assembly or path to the file."<<std::endl
			<<"  OutputName: Name of the output XML file."<<std::endl
			<<"Examples:"<<std::endl
			<<"  tg.exe \"SlimDX, Culture=en, PublicKeyToken=a5d015c7d5a0b012, Version=1.0.0.0\" methods.xml"<<std::endl
			<<"  tg.exe SlimDX.dll methods.xml"<<std::endl;
		return 0;
	}

	std::pair<std::wstring, std::vector<SlimGen::MethodNativeBlocks>> info = SlimGen::GetNativeImageInformation(argv[1]);

	std::wofstream fout(argv[2]);
	fout<<L"<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<std::endl;
	fout<<L"<methods>"<<std::endl;
	for(std::size_t i = 0; i < info.second.size(); ++i) {
		fout<<"    <method name='"<<info.second[i].MethodName<<"'>"<<std::endl;
		for(std::size_t j = 0; j < info.second[i].CodeChunks.size(); ++j) {
			fout<<"        <rva length='"
				<<info.second[i].CodeChunks[j].length
				<<"'>"
				<<info.second[i].CodeChunks[j].startAddr - info.second[i].BaseAddress<<"</rva>"<<std::endl;
		}
		fout<<"    </method>"<<std::endl;
	}
	fout<<L"</methods>"<<std::endl;
}