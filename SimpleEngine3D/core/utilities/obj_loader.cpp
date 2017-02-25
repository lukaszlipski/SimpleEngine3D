#include "obj_loader.h"
#include "../system/file.h"
#include "string.h"

namespace SE3D
{
	OBJLoader::OBJLoader(const char* path)
		:m_VerticesOffset(0), m_TextCoordsOffset(0), m_NormalsOffset(0)
	{
		LoadMeshFromFile(path);
	}

	OBJLoader::~OBJLoader()
	{
	}

	void OBJLoader::LoadMeshFromFile(const char* path)
	{
		FILE meshFile = File::GetInstance().ReadTextSync(path);

		while (true)
		{
			LINE line = File::GetInstance().GetLine(meshFile);

			if(line.Content[0] == 'o' && line.Content[1] == ' ')
			{
				AddNewMesh(line.Content);
			} 
			else if (line.Content[0] == 'v' && line.Content[1] == ' ')
			{
				AddVertex(line.Content);
			}
			else if (line.Content[0] == 'v' && line.Content[1] == 't')
			{
				AddTextCoord(line.Content);
			}
			else if (line.Content[0] == 'v' && line.Content[1] == 'n')
			{
				AddNormal(line.Content);
			}
			else if (line.Content[0] == 'f' && line.Content[1] == ' ')
			{
				AddFace(line.Content);
			}

			if (!line.IsNextLine) { break; }
		}
		ConvertToInternalFormat();
		File::GetInstance().Delete(meshFile);
	}

	void OBJLoader::AddNewMesh(const char* line)
	{
		if(m_Meshes.Size() > 0)
		{
			ConvertToInternalFormat();

			m_VerticesOffset = m_Vertices.Size();
			m_TextCoordsOffset = m_TextCoords.Size();
			m_NormalsOffset = m_Normals.Size();

			m_Vertices.Clear();
			m_Normals.Clear();
			m_TextCoords.Clear();
			m_Indices.Clear();

			m_HasTextureCoordinates = false;
			m_HasNormals = false;
		}

		INTERNAL_MESH_FORMAT mesh;
		mesh.m_Name = line + 2;
		m_Meshes.Push(mesh);
		
	}

	void OBJLoader::AddVertex(const char* line)
	{
		const char* tmpFloat = line + 2;
		float x = String::ToFloat(tmpFloat);
		while (*tmpFloat++ != ' ')
		{
		}
		float y = String::ToFloat(tmpFloat);
		while (*tmpFloat++ != ' ')
		{
		}
		float z = String::ToFloat(tmpFloat);

		m_Vertices.Push(Vector3D(x, y, z));
	}

	void OBJLoader::AddTextCoord(const char* line)
	{
		const char* tmpFloat = line + 3;
		float x = String::ToFloat(tmpFloat);
		while (*tmpFloat++ != ' ')
		{
		}
		float y = String::ToFloat(tmpFloat);

		m_TextCoords.Push(Vector2D(x, y));
	}

	void OBJLoader::AddNormal(const char* line)
	{
		const char* tmpFloat = line + 3;
		float x = String::ToFloat(tmpFloat);
		while (*tmpFloat++ != ' ')
		{
		}
		float y = String::ToFloat(tmpFloat);
		while (*tmpFloat++ != ' ')
		{
		}
		float z = String::ToFloat(tmpFloat);

		m_Normals.Push(Vector3D(x, y, z));
	}

	void OBJLoader::AddFace(const char* line)
	{
		const char* tmpInt = line + 2;
		for (int i = 0; i < 3; i++)
		{
			uint32 vertIndex = String::ToUInt32(tmpInt) - 1;
			while (*tmpInt++ != '/')
			{
			}
			uint32 textIndex = String::ToUInt32(tmpInt);
			if (textIndex)
			{
				m_HasTextureCoordinates = true;
				textIndex--;
			}
			while (*tmpInt++ != '/')
			{
			}
			uint32 normIndex = String::ToUInt32(tmpInt);
			if (normIndex)
			{
				m_HasNormals = true;
				normIndex--;
			}
			m_Indices.Push(OBJindex{ vertIndex,textIndex,normIndex });
			if (i < 2)
			{
				while (*tmpInt++ != ' ')
				{
				}
			}
		}
	}

	void OBJLoader::ConvertToInternalFormat()
	{

		INTERNAL_MESH_FORMAT &mesh = m_Meshes[m_Meshes.Size() - 1];

		int32 currentIndex = 0;
		for (int32 i = 0; i < m_Indices.Size(); i++)
		{
			Vector3D vert = m_Vertices[m_Indices[i].VertexIndex - m_VerticesOffset];
			Vector3D norm;
			if (m_HasNormals)
				norm = m_Normals[m_Indices[i].NormalIndex - m_NormalsOffset];
			Vector2D texCoord;
			if (m_HasTextureCoordinates)
				texCoord = m_TextCoords[m_Indices[i].TextCoordIndex - m_TextCoordsOffset];

			bool isFaceAdded = false;
			for (int32 j = 0; j < mesh.m_Vertices.Size(); j++)
			{
				if (mesh.m_Vertices[j] == vert && mesh.m_Normals[j] == norm && mesh.m_TextCoords[j] == texCoord)
				{		
					mesh.m_Indices.Push(j);
					isFaceAdded = true;
					break;
				}
			}
			
			if (!isFaceAdded)
			{
				mesh.m_Vertices.Push(vert);

				// TODO: calc normals
				mesh.m_Normals.Push(norm);

				if (m_HasTextureCoordinates)
					mesh.m_TextCoords.Push(texCoord);
				else
					mesh.m_TextCoords.Push(Vector2D(0.0f, 0.0f));

				mesh.m_Indices.Push(currentIndex++);
			}

		}

	}
}
