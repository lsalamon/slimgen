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

#include "MethodTemplateBuilder.h"
#include "SigFormat.h"

#include <fstream>

namespace SlimGen {
	void MethodTemplateBuilder::FoundMethod(ICorDebugFunction* function, MethodInformation& method) {
		std::string fileName(method.Method.begin(), method.Method.end());

		CComPtr<ICorDebugCode> codePtr;
		function->GetNativeCode(&codePtr.p);
		CComQIPtr<ICorDebugCode2> code2Ptr(codePtr);

		ULONG32 chunkCount;
		code2Ptr->GetCodeChunks(0, &chunkCount, 0);
		std::vector<CodeChunkInfo> chunks(chunkCount);
		code2Ptr->GetCodeChunks(chunkCount, &chunkCount, &chunks[0]);

		CComPtr<ICorDebugModule> module;
		function->GetModule(&module.p);
		CORDB_ADDRESS baseAddress;
		module->GetBaseAddress(&baseAddress);

		for(int i = 0; i < chunks.size(); ++i) {
			std::stringstream chunkName(directory + fileName);
			chunkName<<i<<".asm";
			std::ofstream out(chunkName.str().c_str());
			out<<";==============================================================================="<<std::endl;
			out<<"; "<<fileName<<std::endl;
			out<<"; chunk: "<<i<<std::endl;
			out<<"; RVA: "<<std::hex<<(chunks[i].startAddr - baseAddress)<<std::endl;
			out<<";==============================================================================="<<std::endl;
			out<<"[ORG "<<std::hex<<(chunks[i].startAddr - baseAddress)<<"h]"<<std::endl;
			out<<std::endl<<"entry_point:"<<std::endl;
			out<<"\t\ttimes "<<chunks[i].length<<" - ($-$$) db 0xCC ; fill remaining space with int3."<<std::endl;
		}
	}
}
