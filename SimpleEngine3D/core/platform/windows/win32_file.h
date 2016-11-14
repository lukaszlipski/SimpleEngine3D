#pragma once

class Win32_File {

private:
	Win32_File() {}


	inline HANDLE Win32_File::PlatformGetFileHandleForRead(const char * filePath)
	{
		HANDLE fileHandle = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if (fileHandle == INVALID_HANDLE_VALUE)
			return INVALID_HANDLE_VALUE;
		return fileHandle;
	}

public:

	static Win32_File& PlatformGetFileAPI()
	{
		static Win32_File *instance = new Win32_File();
		return *instance;
	}

	void* PlatformReadFileSync(const char* filePath);
	bool PlatformWriteFileSync(const char* filePath, void* buffer, UINT32 bufferSize);
	UINT64 PlatformGetFileSize(const char* filePath);
	UINT64 PlatformGetFileSize(HANDLE handle);


};