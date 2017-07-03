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
		Vector3D m_MassCenter;

	public:
		Model(const String& path);
		~Model();

		void Draw(Material *mat = 0) const;
		Mesh* GetMesh(const String& name) const;
		Mesh* GetMesh(uint32 index) const;
		void SetTransformation(const Matrix4D& transformation) { m_Transformation = transformation; }

		inline uint32 GetMeshesSize() const { return m_Meshes.Size(); }
		inline Vector3D GetFurthestLocalPoint() const { return m_FurthestLocalPoint; }
		inline Vector3D GetMassCenter() const { return m_MassCenter; }
	};
}
