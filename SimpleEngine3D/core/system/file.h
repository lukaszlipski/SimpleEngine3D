#pragma once
#include "../utilities/types.h"

namespace SE3D
{
	struct FILE
	{
		uint64 Size;
		int8* Content;
		int8* Seek;
	};

	struct LINE
	{
		uint64 Length;
		char* Content;
		bool IsNextLine;

		LINE()
		{
			Length = 0;
			Content = nullptr;
			IsNextLine = false;
		}

		LINE(const LINE& line)
		{
			this->Content = new char[line.Length + 1];
			this->Length = line.Length;
			this->IsNextLine = line.IsNextLine;
			for (uint32 i = 0; i <= line.Length; i++) { this->Content[i] = line.Content[i]; }
		}

		~LINE() { if (this->Content != nullptr) delete[] this->Content; }
	};

	class File
	{
	private:
		File()
		{
		}

	public:

		static File& GetInstance()
		{
			static File* instance = new File();
			return *instance;
		}

		bool Startup();
		void Shutdown();
		FILE ReadSync(const char* filePath);
		FILE ReadTextSync(const char* filePath);
		bool WriteSync(const char* filePath, void* buffer, unsigned int bufferSize);
		uint64 GetSize(const char* filePath);
		LINE GetLine(FILE& file);
		void Delete(FILE file);
		bool IsLittleEndian() const;
	};
}
