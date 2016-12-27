#include "obj_loader.h"
#include "../system/file.h"
#include "string.h"

namespace SE3D {

	OBJLoader::OBJLoader(const char * path)
	{
		FILE meshFile = File::GetInstance().ReadTextSync(path);
		m_HasNormals = false;
		m_HasTextureCoordinates = false;
		
		while (true)
		{
			LINE line = File::GetInstance().GetLine(meshFile);

			// TODO: Add multiple objects support
			if (line.Content[0] == 'v' && line.Content[1] == ' ')
			{
				const char* tmpFloat = line.Content+2;
				float x = String::ToFloat(tmpFloat);
				while (*tmpFloat++ != ' ') {}
				float y = String::ToFloat(tmpFloat);
				while (*tmpFloat++ != ' ') {}
				float z = String::ToFloat(tmpFloat);

				m_Vertices.Push(Vector3D(x, y, z));
			}
			else if (line.Content[0] == 'v' && line.Content[1] == 't')
			{
				const char* tmpFloat = line.Content + 3;
				float x = String::ToFloat(tmpFloat);
				while (*tmpFloat++ != ' ') {}
				float y = String::ToFloat(tmpFloat);

				m_TextCoords.Push(Vector2D(x, y));
			}
			else if (line.Content[0] == 'v' && line.Content[1] == 'n')
			{
				const char* tmpFloat = line.Content + 3;
				float x = String::ToFloat(tmpFloat);
				while (*tmpFloat++ != ' ') {}
				float y = String::ToFloat(tmpFloat);
				while (*tmpFloat++ != ' ') {}
				float z = String::ToFloat(tmpFloat);

				m_Normals.Push(Vector3D(x, y, z));
			}
			else if (line.Content[0] == 'f' && line.Content[1] == ' ')
			{
				const char* tmpInt = line.Content + 2;
				for (int i = 0; i < 3; i++)
				{
					uint32 vertIndex = String::ToUInt32(tmpInt) -1;
					while (*tmpInt++ != '/') {}
					uint32 textIndex = String::ToUInt32(tmpInt);
					if (textIndex) { m_HasTextureCoordinates = true; textIndex--; }
					while (*tmpInt++ != '/') {}
					uint32 normIndex = String::ToUInt32(tmpInt);
					if (normIndex) { m_HasNormals = true; normIndex--; }
					m_Indices.Push(OBJindex{ vertIndex,textIndex,normIndex});
					if (i < 2) { while (*tmpInt++ != ' ') {} }
				}
			}

			if (!line.IsNextLine) { break; }
		}

		File::GetInstance().Delete(meshFile);
	}

}
