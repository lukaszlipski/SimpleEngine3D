#include <Windows.h>
#include "win32_file.h"


void* Win32_File::PlatformReadFileSync(const char * filePath)
{
	HANDLE fileHandle = PlatformGetFileHandleForRead(filePath);
	if (fileHandle == INVALID_HANDLE_VALUE)
		return nullptr;
	
	UINT64 fileSize = PlatformGetFileSize(fileHandle);
	if (fileSize == -1)
	{
		CloseHandle(fileHandle);
		return nullptr;
	}

	void* buffer = new BYTE[fileSize];
	DWORD bRead;
	if (ReadFile(fileHandle, buffer, fileSize, &bRead, 0) && (bRead == fileSize))
	{
		CloseHandle(fileHandle);
		return buffer;
	}
	else
	{
		CloseHandle(fileHandle);
		delete buffer;
		return nullptr;
	}	
}

bool Win32_File::PlatformWriteFileSync(const char* filePath, void* buffer, UINT32 bufferSize)
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

UINT64 Win32_File::PlatformGetFileSize(const char * filePath)
{
	HANDLE fileHandle = PlatformGetFileHandleForRead(filePath);
	if (fileHandle == INVALID_HANDLE_VALUE)
		return -1;

	UINT64 fileSize = PlatformGetFileSize(fileHandle);

	CloseHandle(fileHandle);

	return fileSize;
}

UINT64 Win32_File::PlatformGetFileSize(HANDLE handle)
{
	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(handle, &fileSize))
		return -1;

	return fileSize.QuadPart;
}
