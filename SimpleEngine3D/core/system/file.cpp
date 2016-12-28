#include "file.h"

namespace SE3D {

	bool File::Startup()
	{
		return true;
	}
	void File::Shutdown()
	{
	}

	LINE File::GetLine(FILE& file)
	{
		LINE line;
		if (file.Content == nullptr) { return line; }

		line.Length = 0;
		while (*file.Seek != '\0' && *file.Seek++ != '\n')
		{
			line.Length++;
		}
		if (*file.Seek != '\0') { line.IsNextLine = true; } else { line.IsNextLine = false; }
		line.Content = new char[line.Length + 1];
		for (uint32 i = 0; i < line.Length; i++)
		{
			line.Content[i] = (file.Seek - line.Length - 1)[i];
		}
		line.Content[line.Length] = '\0';

		return line;
	}

	void File::Delete(FILE file)
	{
		if (file.Content != nullptr)
			delete[] file.Content;
	}

}