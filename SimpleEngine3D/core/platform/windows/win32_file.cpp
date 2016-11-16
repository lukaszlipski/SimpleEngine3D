#include "../system/file.h"
#include <Windows.h>

namespace SE3D {

	FILE File::ReadSync(const char * filePath)
	{
		HANDLE fileHandle = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if (fileHandle == INVALID_HANDLE_VALUE)
			return FILE{ 0,nullptr };

		LARGE_INTEGER fileSizeStruct;
		if (!GetFileSizeEx(fileHandle, &fileSizeStruct))
			return FILE{ 0,nullptr };

		UINT64 fileSize = fileSizeStruct.QuadPart;
		if (fileSize == 0)
		{
			CloseHandle(fileHandle);
			return FILE{ 0,nullptr };
		}

		void* buffer = new BYTE[fileSize];
		DWORD bRead;
		if (ReadFile(fileHandle, buffer, fileSize, &bRead, 0) && (bRead == fileSize))
		{
			CloseHandle(fileHandle);
			return FILE{ fileSize,buffer };
		}
		else
		{
			CloseHandle(fileHandle);
			delete buffer;
			return FILE{ 0,nullptr };
		}
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

	uint64_t File::GetSize(const char * filePath)
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