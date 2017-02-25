#include "model_loader.h"

namespace SE3D
{
	INTERNAL_MESH_FORMAT* ModelLoader::GetMesh(uint32 index) const
	{
		if (index < m_Meshes.Size() && index >= 0)
			return &m_Meshes[index];
		return nullptr;
	}
}
