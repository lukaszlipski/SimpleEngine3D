#pragma once
#include "string.h"
#include "../math/vector3d.h"

namespace SE3D
{
	struct INTERNAL_MESH_FORMAT
	{
		String m_Name;
		DynamicArray<Vector3D> m_Vertices;
		DynamicArray<Vector2D> m_TextCoords;
		DynamicArray<Vector3D> m_Normals;
		DynamicArray<Vector3D> m_Tangents;
		DynamicArray<uint32> m_Indices;

		INTERNAL_MESH_FORMAT& operator=(const INTERNAL_MESH_FORMAT& right)
		{
			m_Name = right.m_Name;
			m_Vertices = right.m_Vertices;
			m_TextCoords = right.m_TextCoords;
			m_Normals = right.m_Normals;
			m_Tangents = right.m_Tangents;
			m_Indices = right.m_Indices;
			return *this;
		}
	};

	class ModelLoader
	{
	protected:
		DynamicArray<INTERNAL_MESH_FORMAT> m_Meshes;

	public:
		virtual ~ModelLoader() = default;
		inline uint32 GetMeshesSize() const { return m_Meshes.Size(); }
		INTERNAL_MESH_FORMAT* GetMesh(uint32 index) const;

	protected:
		virtual void ConvertToInternalFormat() = 0;
	};
}
