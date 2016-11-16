#pragma once

class File {

private:
	File() {}
public:

	static File& GetInstance()
	{
		static File *instance = new File();
		return *instance;
	}

	void* ReadSync(const char * filePath);
	bool WriteSync(const char* filePath, void* buffer, unsigned int bufferSize);
	long long GetSize(const char * filePath);

};