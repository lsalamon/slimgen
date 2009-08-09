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

#include "Injection.h"
#include <iostream>

struct TempFile
{
	TempFile(std::wstring const& imagePath) {
		wchar_t tempPath[MAX_PATH];
		if (!GetTempPath(MAX_PATH, tempPath))
			throw std::runtime_error("Unable to get temporary file path.");

		wchar_t tempName[MAX_PATH];
		if (!GetTempFileName(tempPath, L"SGC", 0, tempName))
			throw std::runtime_error("Unable to get temporary file name.");

		if (!CopyFile(imagePath.c_str(), tempName, false))
			throw std::runtime_error("Unable to copy image file to temporary file.");

		fileName = tempName;
	}

	operator wchar_t const*() const { return fileName.c_str(); }
	~TempFile() { if (!fileName.empty()) DeleteFile(fileName.c_str()); }

	std::wstring fileName;
};

class FileMappingView
{
public:
	FileMappingView(HANDLE fileHandle)
	{
		fileMapping = CreateFileMapping(fileHandle, NULL, PAGE_READWRITE, 0, 0, NULL);
		if (fileMapping == NULL || fileMapping == INVALID_HANDLE_VALUE)
			throw std::runtime_error("Unable to create file mapping.");

		basePointer = MapViewOfFile(fileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	}

	~FileMappingView()
	{
		ScopedHandle handle(fileMapping);
		if (basePointer != NULL)
			UnmapViewOfFile(basePointer);
	}

	void Unmap() { 
		ScopedHandle handle(fileMapping);
		fileMapping = INVALID_HANDLE_VALUE;
		if(basePointer)
			UnmapViewOfFile(basePointer);
		basePointer = 0;
	}
	char *BasePointer() { return reinterpret_cast<char*>(basePointer); }
	operator void*() { return basePointer; }

private:
	LPVOID basePointer;
	HANDLE fileMapping;
};

int InjectNativeCode(const std::wstring &imagePath, const std::vector<MethodDescriptor> &methods)
{
	assert(sizeof(short) == 2);
	assert(sizeof(int) == 4);

	try {
		TempFile fileCleanup(imagePath);

		ScopedHandle fileHandle = CreateFile(fileCleanup, GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, 0);
		if (fileHandle == NULL || fileHandle == INVALID_HANDLE_VALUE)
			throw std::runtime_error("Unable to open temporary image file");

		FileMappingView fileView(fileHandle);

		char *image = fileView.BasePointer();
		IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(image);
		if(dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
			throw std::runtime_error("Invalid PE file header.");

		IMAGE_NT_HEADERS* ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(image + dosHeader->e_lfanew);
		if(ntHeader->Signature != IMAGE_NT_SIGNATURE)
			throw std::runtime_error("Invalid PE file header.");

		IMAGE_SECTION_HEADER* sectionHeaders = reinterpret_cast<IMAGE_SECTION_HEADER*>(reinterpret_cast<char*>(&ntHeader->OptionalHeader) + ntHeader->FileHeader.SizeOfOptionalHeader);

		for (std::vector<MethodDescriptor>::const_iterator method = methods.begin(); method != methods.end(); method++)
		{
			IMAGE_SECTION_HEADER* section;
			for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; ++i)
			{
				
				if (method->BaseAddress > sectionHeaders[i].VirtualAddress && method->BaseAddress <= sectionHeaders[i].VirtualAddress + sectionHeaders[i].Misc.VirtualSize) {
					section = sectionHeaders + i;
					break;
				}
			}

			if (section == 0)
				continue;

			long fileOffset = method->BaseAddress - (section->VirtualAddress - section->PointerToRawData);
			memcpy(fileView.BasePointer() + fileOffset, method->Data, method->Length);
		}

		fileView.Unmap();
		fileHandle.reset();
		if (!CopyFile(fileCleanup, imagePath.c_str(), false)) {
			DWORD error = GetLastError();
			throw std::runtime_error("Unable to copy temporary image back to image. Administrative rights are required to perform this action.");
		}
	} catch(std::runtime_error& error) {
		std::cout<<error.what()<<std::endl;
		return -1;
	}

	return 0;
}