#pragma once
#include "../containers/dynamic_array.h"
#include "../math/math.h"
#include "string.h"

namespace SE3D
{
	struct OBJindex
	{
		uint32 VertexIndex;
		uint32 TextCoordIndex;
		uint32 NormalIndex;
	};

	struct INTERNAL_MESH_FORMAT
	{
		String m_Name;
		DynamicArray<Vector3D> m_Vertices;
		DynamicArray<Vector2D> m_TextCoords;
		DynamicArray<Vector3D> m_Normals;
		DynamicArray<uint32> m_Indices;

		INTERNAL_MESH_FORMAT& operator=(const INTERNAL_MESH_FORMAT& right)
		{
			m_Name = right.m_Name;
			m_Vertices = right.m_Vertices;
			m_TextCoords = right.m_TextCoords;
			m_Normals = right.m_Normals;
			m_Indices = right.m_Indices;
			return *this;
		}

	};

	class OBJLoader
	{
	private:
		DynamicArray<INTERNAL_MESH_FORMAT> m_Meshes;
		DynamicArray<Vector3D> m_Vertices;
		DynamicArray<Vector2D> m_TextCoords;
		DynamicArray<Vector3D> m_Normals;
		DynamicArray<OBJindex> m_Indices;
		uint32 m_VerticesOffset;
		uint32 m_TextCoordsOffset;
		uint32 m_NormalsOffset;
		bool m_HasNormals;
		bool m_HasTextureCoordinates;

	public:
		OBJLoader(const char* path);
		~OBJLoader();

		inline uint32 GetMeshesSize() const { return m_Meshes.Size(); }
		inline INTERNAL_MESH_FORMAT* GetMesh(uint32 index) const
		{
			if (index < m_Meshes.Size() && index >= 0)
				return &m_Meshes[index];
			return nullptr;
		}

	private:
		void LoadMeshFromFile(const char* path);
		void AddNewMesh(const char* line);
		void AddVertex(const char* line);
		void AddTextCoord(const char* line);
		void AddNormal(const char* line);
		void AddFace(const char* line);
		void ConvertToInternalFormat();
	};
}
