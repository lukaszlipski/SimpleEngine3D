#pragma once
#include "../utilities/types.h"

namespace SE3D {

	struct FILE
	{
		uint64 Size;
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
		FILE ReadTextSync(const char * filePath);
		bool WriteSync(const char* filePath, void* buffer, unsigned int bufferSize);
		uint64 GetSize(const char * filePath);
		void Delete(FILE file);

	};

}