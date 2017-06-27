#include "model.h"
#include "../utilities/obj_loader.h"

namespace SE3D
{
	Model::Model(const String& path)
		: m_Transformation(Matrix4D::Identity())
	{
		OBJLoader loader(path.CString());
		for (uint32 i = 0; i < loader.GetMeshesSize(); i++)
		{
			m_Meshes.Push(new Mesh(*loader.GetMesh(i)));
		}
		m_TransformationStringID = String("u_model").GetStringID();
		m_FurthestLocalPoint = loader.GetFurthestPoint();
	}

	Model::~Model()
	{
		m_Meshes.Clear(true);
	}

	void Model::Draw() const
	{
		for (uint32 i = 0; i < m_Meshes.Size(); i++)
		{
			m_Meshes[i]->GetMaterial().SetParamMatrix4D(m_TransformationStringID, m_Transformation);
			m_Meshes[i]->Draw();
		}
	}

	Mesh* Model::GetMesh(const String& name) const
	{
		for (uint32 i = 0; i < m_Meshes.Size(); i++)
		{
			if (name == m_Meshes[i]->GetName())
			{
				return m_Meshes[i];
			}
		}
		return nullptr;
	}

	Mesh* Model::GetMesh(uint32 index) const
	{
		if (index >= 0 && index < m_Meshes.Size())
			return m_Meshes[index];
		return nullptr;
	}
}
