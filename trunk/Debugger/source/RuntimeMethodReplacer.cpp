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

#include "RuntimeMethodReplacer.h"
#include "SigFormat.h"

namespace SlimGen
{
    void RuntimeMethodReplacer::FoundMethod(ICorDebugFunction* function, MethodInformation& method)
    {
        std::string name(method.Method.begin(), method.Method.end());
        if (method.Replaced)
            throw std::runtime_error(std::string("Attempt to replace method ") + name + " multiple times.");

        CComPtr<ICorDebugCode> codePtr;
        function->GetNativeCode(&codePtr.p);
        CComQIPtr<ICorDebugCode2> code2Ptr(codePtr);

        ULONG32 chunkCount;
        code2Ptr->GetCodeChunks(0, &chunkCount, 0);
        std::vector<CodeChunkInfo> chunks(chunkCount);
        code2Ptr->GetCodeChunks(chunkCount, &chunkCount, &chunks[0]);

        if (method.CompiledData.size() != chunkCount)
            throw std::runtime_error(name + " does not have the correct number of code chunks.");

        for (size_t i = 0; i < chunks.size(); i++)
        {
            if (method.CompiledData[i].size() > chunks[i].length)
            {
                std::stringstream error;
                error << "Chunk " << i << " for method " << name << " does not have the right code size.";
                throw std::runtime_error(error.str());
            }

            SIZE_T written;
            debugProcess->WriteMemory(chunks[i].startAddr, method.CompiledData[i].size(), reinterpret_cast<BYTE*>(&method.CompiledData[i][0]), &written);

            if (written != method.CompiledData[i].size())
            {
                std::stringstream error;
                error << "Chunk " << i << " for method " << name << " failed to write completely.";
                throw std::runtime_error(error.str());
            }
        }
        method.Replaced = true;
    }
}