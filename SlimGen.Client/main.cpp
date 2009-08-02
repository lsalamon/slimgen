#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace InjectionResult
{
	enum Code
	{
		CouldNotCopyImage,
		InvalidImageFile,
		InvalidMethodRVA,
		MissingReplacementFile,
		CouldNotReplaceImage,
		Success
	};
}

struct MethodDescriptor
{
	long RVA;
	std::wstring ReplacementFile;
};

struct PESection
{
	long VirtualAddress;
	long RawOffset;
};

int main()
{
}

class TempFileCleanup
{
private:
	std::wstring fileName;

public:
	TempFileCleanup(const std::wstring &fileName) : fileName(fileName) { }
	~TempFileCleanup() { DeleteFile(fileName.c_str()); }
};

InjectionResult::Code InjectNativeCode(const std::wstring &imagePath, const std::vector<MethodDescriptor> &methodDescriptors)
{
	// STEP 1: Copy native image into a temporary file for processing
	wchar_t tempPath[MAX_PATH];
	if (!GetTempPath(MAX_PATH, tempPath))
		return InjectionResult::CouldNotCopyImage;

	wchar_t tempFileName[MAX_PATH];
	if (!GetTempFileName(tempPath, L"SGC", 0, tempFileName))
		return InjectionResult::CouldNotCopyImage;

	if (!CopyFile(imagePath.c_str(), tempFileName, true))
		return InjectionResult::CouldNotCopyImage;

	// STEP 2: Extract section headers so we can index RVAs
	TempFileCleanup cleanup(tempFileName);
	std::fstream image(tempFileName);
	if (!image)
		return InjectionResult::InvalidImageFile;

	std::streampos offset = 0;
	image.seekg(0x3c);	// skip to the PE header offset
	if (!image.read(reinterpret_cast<char*>(&offset), 4))
		return InjectionResult::InvalidImageFile;

	char signature[4];
	image.seekg(offset);	// skip to the PE header
	if (!image.read(signature, 4))	// ensure that we're at the right spot (PE signature is "PE\0\0")
		return InjectionResult::InvalidImageFile;
	if (signature[0] != 'P' || signature[1] != 'E' || signature[2] != 0 || signature[3] != 0)
		return InjectionResult::InvalidImageFile;

	short sectionCount = 0;
	image.seekg(2, std::ios::cur);
	if (!image.read(reinterpret_cast<char*>(&sectionCount), 2))
		return InjectionResult::InvalidImageFile;
	if (sectionCount <= 0 || sectionCount > 96)
		return InjectionResult::InvalidImageFile;

	short sizeOfOptionalHeader = 0;
	image.seekg(12, std::ios::cur);
	if (!image.read(reinterpret_cast<char*>(&sizeOfOptionalHeader), 2))
		return InjectionResult::InvalidImageFile;
	image.seekg((int)offset + 4 + 20 + sizeOfOptionalHeader);  // skip to the start of the section table

	std::vector<PESection> sections(sectionCount);
	for (int i = 0; i < sectionCount; i++)
	{
		PESection section;

		image.seekg(12, std::ios::cur);
		if (!image.read(reinterpret_cast<char*>(&section.VirtualAddress), 4))
			return InjectionResult::InvalidImageFile;

		image.seekg(4, std::ios::cur);
		if (!image.read(reinterpret_cast<char*>(&section.RawOffset), 4))
			return InjectionResult::InvalidImageFile;

		image.seekg(16, std::ios::cur);
	}
	std::reverse(sections.begin(), sections.end());

	// STEP 3: Replace each method body with the given native data
	for (std::vector<MethodDescriptor>::const_iterator method = methodDescriptors.begin(); method != methodDescriptors.end(); method++)
	{
		std::vector<PESection>::const_iterator first = sections.begin();
		for ( ; first != sections.end(); first++)
		{
			if (method->RVA > first->VirtualAddress)
				break;
		}

		if (first == sections.end())
			return InjectionResult::InvalidMethodRVA;

		std::streampos fileOffset = method->RVA - first->VirtualAddress + first->RawOffset;
		image.seekg(fileOffset);

		std::ifstream replacementFile(method->ReplacementFile.c_str());
		if (!replacementFile)
			return InjectionResult::MissingReplacementFile;

		replacementFile.seekg(0, std::ios::end);
		long size = replacementFile.tellg();
		std::vector<char> objData(size);
		replacementFile.read(&objData[0], size);

		image.write(&objData[0], size);
	}

	// STEP 4: Copy the native image back to the original location
	if (!CopyFile(tempFileName, imagePath.c_str(), false))
		return InjectionResult::CouldNotReplaceImage;

	return InjectionResult::Success;
}