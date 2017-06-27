#pragma once
#include "../containers/dynamic_array.h"
#include "mesh.h"
#include "../math/matrix4d.h"

namespace SE3D
{
	class Model
	{
	private:
		DynamicArray<Mesh*> m_Meshes;
		Matrix4D m_Transformation;
		uint32 m_TransformationStringID;
		Vector3D m_FurthestLocalPoint;

	public:
		Model(const String& path);
		~Model();

		void Draw() const;
		Mesh* GetMesh(const String& name) const;
		Mesh* GetMesh(uint32 index) const;
		void SetTransformation(const Matrix4D& transformation) { m_Transformation = transformation; }

		inline uint32 GetMeshesSize() const { return m_Meshes.Size(); }
		inline Vector3D GetFurthestLocalPoint() const { return m_FurthestLocalPoint; }
	};
}
