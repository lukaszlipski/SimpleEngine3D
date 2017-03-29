#pragma once
#include "material.h"
#include "../math/vector3d.h"

namespace SE3D
{
	struct INTERNAL_MESH_FORMAT;

	struct VERTEX
	{
		Vector3D m_Position;
		Vector3D m_Normal;
		Vector2D m_UV;
		Vector3D m_Tangent;
	};

	class Mesh
	{
	private:
		String m_Name;
		Material m_Material;
		uint32 m_VAO;
		uint32 m_VBO;
		uint32 m_IBO;
		uint32 m_Size;

	public:
		Mesh(const INTERNAL_MESH_FORMAT& mesh);
		Mesh();
		~Mesh();

		void Draw() const;
		inline void SetMaterial(const Material& material) { m_Material = material; }
		inline Material& GetMaterial() { return m_Material; }
		inline const String& GetName() const { return m_Name; }

	};
}
