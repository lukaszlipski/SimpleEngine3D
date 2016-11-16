#pragma once
#include <cstdint>

namespace SE3D {

	struct FILE
	{
		uint64_t Size;
		void* Content;
	};

	class File {

	private:
		File() {}
	public:

		static File& GetInstance()
		{
			static File *instance = new File();
			return *instance;
		}

		FILE ReadSync(const char * filePath);
		bool WriteSync(const char* filePath, void* buffer, unsigned int bufferSize);
		uint64_t GetSize(const char * filePath);
		void Delete(FILE file);

	};

}