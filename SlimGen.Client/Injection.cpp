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

struct ScopedHandle
{
	ScopedHandle() : handle(INVALID_HANDLE_VALUE) { }
	ScopedHandle(HANDLE handle) : handle(handle) { }
	~ScopedHandle() { if (handle != INVALID_HANDLE_VALUE && handle != NULL) CloseHandle(handle); }

	HANDLE release() { HANDLE tmp = handle; handle = INVALID_HANDLE_VALUE; return tmp; }
	operator HANDLE&() { return handle; }

	HANDLE handle;
};

struct TempFile
{
	TempFile() {
		wchar_t tempPath[MAX_PATH];
		if (!GetTempPath(MAX_PATH, tempPath))
			return;

		wchar_t tempName[MAX_PATH];
		if (!GetTempFileName(tempPath, L"SGC", 0, tempName))
			return;

		fileName = tempName;
	}

	operator wchar_t const*() const { if(fileName.empty()) return 0; return fileName.c_str(); }
	~TempFile() { if (fileName.empty()) DeleteFile(fileName.c_str()); }

	std::wstring fileName;
};

class FileMappingView
{
public:
	FileMappingView(HANDLE fileHandle)
	{
		fileMapping = CreateFileMapping(fileHandle, NULL, PAGE_READWRITE, 0, 0, NULL);
		if (fileMapping == NULL || fileMapping == INVALID_HANDLE_VALUE)
			return;

		basePointer = MapViewOfFile(fileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	}

	~FileMappingView()
	{
		ScopedHandle handle(fileMapping);
		if (basePointer != NULL)
			UnmapViewOfFile(basePointer);
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

	TempFile fileCleanup;
	if(!fileCleanup)
		return 2;

	if (!CopyFile(imagePath.c_str(), fileCleanup, true))
		return 3;

	ScopedHandle fileHandle = CreateFile(imagePath.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandle == NULL || fileHandle == INVALID_HANDLE_VALUE)
		return 4;

	FileMappingView fileView(fileHandle);
	if (!fileView)
		return 5;

	char *image = fileView.BasePointer();
	int offset = *reinterpret_cast<int*>(image + 0x3c);
	char *header = image + offset;
	if (header[0] != 'P' || header[1] != 'E' || header[2] != 0 || header[3] != 0)
		return 6;

	short sectionCount = *reinterpret_cast<short*>(header + 6);
	if (sectionCount <= 0 || sectionCount > 96)
		return 7;

	short sizeOfOptionalHeader = *reinterpret_cast<short*>(header + 18);
	image += offset + 24 + sizeOfOptionalHeader;

	std::vector<IMAGE_SECTION_HEADER> sections(sectionCount);
	for (int i = 0; i < sectionCount; i++)
	{
		sections.push_back(*reinterpret_cast<IMAGE_SECTION_HEADER*>(image));
		image += IMAGE_SIZEOF_SECTION_HEADER;
	}

	for (std::vector<MethodDescriptor>::const_iterator method = methods.begin(); method != methods.end(); method++)
	{
		std::vector<IMAGE_SECTION_HEADER>::const_iterator first = sections.begin();
		for ( ; first != sections.end(); first++)
		{
			if (method->BaseAddress > first->VirtualAddress && method->BaseAddress <= first->VirtualAddress + first->Misc.VirtualSize)
				break;
		}

		if (first == sections.end())
			continue;

		ScopedHandle replacementFile = CreateFile(method->ReplacementFile.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		if(replacementFile == INVALID_HANDLE_VALUE || replacementFile == NULL)
			continue;

		DWORD size = GetFileSize(replacementFile, 0);
		if(size > method->Length)
			continue;

		long fileOffset = method->BaseAddress - first->VirtualAddress + first->PointerToRawData;
		ReadFile(replacementFile, fileView.BasePointer() + fileOffset, size, &size, 0);
	}

	if (!CopyFile(fileCleanup, imagePath.c_str(), false))
		return 8;

	return 0;
}