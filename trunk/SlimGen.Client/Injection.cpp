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

struct ScopedHandle {
	ScopedHandle() : handle(INVALID_HANDLE_VALUE) { }
	ScopedHandle(HANDLE handle) : handle(handle) { }
	~ScopedHandle() { if(handle != INVALID_HANDLE_VALUE) CloseHandle(handle); }
	HANDLE release() { HANDLE tmp = handle; handle = INVALID_HANDLE_VALUE; return tmp; }
	operator HANDLE&() { return handle; }
	HANDLE handle;
};

bool CopyTemporaryImage(const std::wstring &imagePath, wchar_t *tempFileName)
{
	wchar_t tempPath[MAX_PATH];
	if (!GetTempPath(MAX_PATH, tempPath))
		return false;

	if (!GetTempFileName(tempPath, L"SGC", 0, tempFileName))
		return false;

	if (!CopyFile(imagePath.c_str(), tempFileName, true))
		return false;

	return true;
}

char *MapImageFile(const std::wstring &imagePath, HANDLE *file, HANDLE *mapping)
{
	ScopedHandle fileHandle = CreateFile(imagePath.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandle == NULL || fileHandle == INVALID_HANDLE_VALUE)
		return NULL;

	ScopedHandle fileMapping = CreateFileMapping(fileHandle, NULL, PAGE_READWRITE, 0, 0, NULL);
	if (fileMapping == NULL)
	{
		return NULL;
	}

	LPVOID pointer = MapViewOfFile(fileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pointer == NULL)
	{
		return NULL;
	}

	*file = fileHandle;
	*mapping = fileMapping;

	fileHandle.release();
	fileMapping.release();

	return reinterpret_cast<char*>(pointer);
}

void UnmapImageFile(HANDLE fileHandle, HANDLE fileMapping, char *image)
{
	UnmapViewOfFile(image);
	CloseHandle(fileMapping);
	CloseHandle(fileHandle);
}

bool ParsePEHeaders(char *image, std::vector<IMAGE_SECTION_HEADER> &sections)
{
	int offset = *reinterpret_cast<int*>(image + 0x3c);
	char *header = image + offset;
	if (header[0] != 'P' || header[1] != 'E' || header[2] != 0 || header[3] != 0)
		return false;

	short sectionCount = *reinterpret_cast<short*>(header + 6);
	if (sectionCount <= 0 || sectionCount > 96)
		return false;

	short sizeOfOptionalHeader = *reinterpret_cast<short*>(header + 18);
	image += offset + 24 + sizeOfOptionalHeader;
	sections.reserve(sectionCount);

	for (int i = 0; i < sectionCount; i++)
	{
		sections.push_back(*reinterpret_cast<IMAGE_SECTION_HEADER*>(image));
		image += IMAGE_SIZEOF_SECTION_HEADER;
	}

	return true;
}

int InjectNativeCode(const std::wstring &imagePath, const std::vector<MethodDescriptor> &methodDescriptors)
{
	assert(sizeof(short) == 2);
	assert(sizeof(int) == 4);

	wchar_t tempFileName[MAX_PATH];
	if (!CopyTemporaryImage(imagePath, tempFileName))
		return 1;

	HANDLE fileHandle, fileMapping;
	char *image = MapImageFile(tempFileName, &fileHandle, &fileMapping);
	if (image == NULL)
	{
		DeleteFile(tempFileName);
		return 2;
	}

	std::vector<IMAGE_SECTION_HEADER> sections;
	if (!ParsePEHeaders(image, sections))
	{
		UnmapImageFile(fileHandle, fileMapping, image);
		DeleteFile(tempFileName);
		return 3;
	}

	for (std::vector<MethodDescriptor>::const_iterator method = methodDescriptors.begin(); method != methodDescriptors.end(); method++)
	{
		std::vector<IMAGE_SECTION_HEADER>::const_iterator first = sections.begin();
		for ( ; first != sections.end(); first++)
		{
			if (method->RVA > first->VirtualAddress && method->RVA <= first->VirtualAddress + first->Misc.VirtualSize)
				break;
		}

		if (first == sections.end())
			continue;

		ScopedHandle replacementFile = CreateFile(method->ReplacementFile.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		if(replacementFile == INVALID_HANDLE_VALUE)
			continue;

		DWORD size = GetFileSize(replacementFile, 0);

		if(size > method->MaxSize) {
			continue;
		}

		long fileOffset = method->RVA - first->VirtualAddress + first->PointerToRawData;
		ReadFile(replacementFile, image + fileOffset, size, &size, 0);
	}

	int result = 0;
	if (!CopyFile(tempFileName, imagePath.c_str(), false))
		result = 4;

	UnmapImageFile(fileHandle, fileMapping, image);
	DeleteFile(tempFileName);

	return result;
}