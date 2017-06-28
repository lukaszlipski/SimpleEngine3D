#include "obj_loader.h"
#include "../system/file.h"
#include "string.h"

namespace SE3D
{
	OBJLoader::OBJLoader(const char* path)
		: m_VerticesOffset(0), m_TextCoordsOffset(0), m_NormalsOffset(0)
	{
		LoadMeshFromFile(path);

		for (uint32 i = 0; i < m_Vertices.Size(); ++i)
		{
			if (m_FurthestPoint.LengthSquared() < m_Vertices[i].LengthSquared())
			{
				m_FurthestPoint = m_Vertices[i];
			}
			m_Center += m_Vertices[i];
		}

		m_Center /= static_cast<float>(m_Vertices.Size());

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

			if (line.Content[0] == 'o' && line.Content[1] == ' ')
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
		if (m_Meshes.Size() > 0)
		{
			ConvertToInternalFormat();

			m_VerticesOffset += m_Vertices.Size();
			m_TextCoordsOffset += m_TextCoords.Size();
			m_NormalsOffset += m_Normals.Size();

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

		Vector3D newVert = Vector3D(x, y, z);
		m_Vertices.Push(newVert);

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
			m_Indices.Push(OBJindex{vertIndex,textIndex,normIndex});
			if (i < 2)
			{
				while (*tmpInt++ != ' ')
				{
				}
			}
		}
	}

	void OBJLoader::CalculateTangents()
	{
		// TODO : implement calculating tangets for mesh
		INTERNAL_MESH_FORMAT& mesh = m_Meshes[m_Meshes.Size() - 1];
		for(uint32 i=0;i<mesh.m_Indices.Size();i+=3)
		{
			uint32 index0 = mesh.m_Indices[i];
			uint32 index1 = mesh.m_Indices[i+1];
			uint32 index2 = mesh.m_Indices[i+2];

			Vector3D edge1 = mesh.m_Vertices[index1] - mesh.m_Vertices[index0];
			Vector3D edge2 = mesh.m_Vertices[index2] - mesh.m_Vertices[index0];

			Vector2D uv1 = mesh.m_TextCoords[index1] - mesh.m_TextCoords[index0];
			Vector2D uv2 = mesh.m_TextCoords[index2] - mesh.m_TextCoords[index0];

			float f = 1.0f / (uv1.x * uv2.y - uv2.x * uv1.y);

			Vector3D tangent;
			tangent.x = (uv2.y * edge1.x - uv1.y * edge2.x) * f;
			tangent.y = (uv2.y * edge1.y - uv1.y * edge2.y) * f;
			tangent.z = (uv2.y * edge1.z - uv1.y * edge2.z) * f;

			Vector3D biTangent;
			biTangent.x = (-uv2.x * edge1.x + uv1.x * edge2.x) * f;
			biTangent.y = (-uv2.x * edge1.y + uv1.x * edge2.y) * f;
			biTangent.z = (-uv2.x * edge1.z + uv1.x * edge2.z) * f;

			if (mesh.m_Normals[index0].Cross(tangent).Dot(biTangent) < 0.0f)
				tangent *= -1.0f;

			mesh.m_Tangents[index0] += tangent;
			mesh.m_Tangents[index1] += tangent;
			mesh.m_Tangents[index2] += tangent;
		}

		for (uint32 i = 0; i < mesh.m_Tangents.Size(); i++)
		{
			mesh.m_Tangents[i] = mesh.m_Tangents[i].Normalize();
		}
	}

	void OBJLoader::ConvertToInternalFormat()
	{
		INTERNAL_MESH_FORMAT& mesh = m_Meshes[m_Meshes.Size() - 1];

		int32 currentIndex = 0;
		for (uint32 i = 0; i < m_Indices.Size(); i++)
		{
			Vector3D vert = m_Vertices[m_Indices[i].VertexIndex - m_VerticesOffset];
			Vector3D norm;
			if (m_HasNormals)
				norm = m_Normals[m_Indices[i].NormalIndex - m_NormalsOffset];
			Vector2D texCoord;
			if (m_HasTextureCoordinates)
				texCoord = m_TextCoords[m_Indices[i].TextCoordIndex - m_TextCoordsOffset];

			bool isFaceAdded = false;
			for (uint32 j = 0; j < mesh.m_Vertices.Size(); j++)
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

				mesh.m_Tangents.Push(Vector3D(0, 0, 0));
				mesh.m_Indices.Push(currentIndex++);
			}
		}
		CalculateTangents();

	}
}
