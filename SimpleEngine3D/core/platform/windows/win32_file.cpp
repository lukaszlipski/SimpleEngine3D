#include <Windows.h>
#include "../system/file.h"
#include "../utilities/assertion.h"

namespace SE3D {


	FILE File::ReadSync(const char * filePath)
	{
		HANDLE fileHandle = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if (fileHandle == INVALID_HANDLE_VALUE)
			return FILE{ 0,nullptr,nullptr };

		LARGE_INTEGER fileSizeStruct;
		if (!GetFileSizeEx(fileHandle, &fileSizeStruct))
			return FILE{ 0,nullptr,nullptr };

		UINT64 fileSize = fileSizeStruct.QuadPart;
		if (fileSize == 0)
		{
			CloseHandle(fileHandle);
			return FILE{ 0,nullptr,nullptr };
		}
		Assert(fileSize <= MAX_UINT32)
		
		void* buffer = new BYTE[fileSize+1];
		DWORD bRead;
		if (ReadFile(fileHandle, buffer, static_cast<uint32>(fileSize), &bRead, 0) && (bRead == fileSize))
		{
			CloseHandle(fileHandle);
			return FILE{ fileSize,buffer,(char*)buffer };
		}
		else
		{
			CloseHandle(fileHandle);
			delete buffer;
			return FILE{ 0,nullptr,nullptr };
		}
	}

	FILE File::ReadTextSync(const char * filePath)
	{
		FILE textFile = ReadSync(filePath);


		char *tmp = (char*)(textFile.Content);
		for (int i = 0; i <= textFile.Size; i++)
		{
			if (*tmp == '\r') { *tmp = ' '; }
			if (i == textFile.Size) {
				*tmp = '\0';
			}
			tmp++;
		}
		return textFile;
	}

	bool File::WriteSync(const char* filePath, void* buffer, unsigned int bufferSize)
	{
		HANDLE fileHandle = CreateFile(filePath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		if (fileHandle == INVALID_HANDLE_VALUE)
			return false;

		DWORD bWrite;
		if (WriteFile(fileHandle, buffer, bufferSize, &bWrite, 0))
		{
			CloseHandle(fileHandle);
			return (bWrite == bufferSize);
		}
		else
		{
			CloseHandle(fileHandle);
			return false;
		}
	}

	uint64 File::GetSize(const char * filePath)
	{
		HANDLE fileHandle = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if (fileHandle == INVALID_HANDLE_VALUE)
			return 0;

		LARGE_INTEGER fileSizeStruct;
		if (!GetFileSizeEx(fileHandle, &fileSizeStruct))
			return 0;

		CloseHandle(fileHandle);

		return fileSizeStruct.QuadPart;
	}

}