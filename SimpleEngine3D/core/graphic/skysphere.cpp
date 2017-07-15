#include "skysphere.h"
#include "..\utilities\string.h"
#include "..\system\texture_manager.h"
#include "deferred_renderer.h"

namespace SE3D
{

	Skysphere::Skysphere(String path, bool srgb)
		: m_Material("skysphere.vs", "skysphere.fs"), m_Sphere("resources/models/skysphere.obj")
	{
		m_Texture = TextureManager::GetInstance().Get(path, srgb);
		m_SkysphereTextureNameID = String("u_skysphereTexture").GetStringID();
		m_Material.SetParamTexture2D(m_SkysphereTextureNameID,*m_Texture);
	}

	void Skysphere::Draw(DeferredRenderer* renderer)
	{
		if (m_Texture)
		{
			m_Material.SetParamMatrix4D(String("u_view").GetStringID(), renderer->GetCamera()->GetView());
			m_Material.SetParamMatrix4D(String("u_projection").GetStringID(), renderer->GetCamera()->GetProjection());
			Matrix4D correction;
			correction.SetColumn(3, Vector4D(renderer->GetCamera()->GetOwner()->GetRotation().GetForward() * -1,1.0f));
			m_Material.SetParamMatrix4D(String("u_correction").GetStringID(), correction);
			m_Sphere.Draw(&m_Material);
		}
	}

}