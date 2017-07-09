#include "directional_light_component.h"
#include "../deferred_renderer.h"
#include "../system/graphics.h"
#include "../math/math.h"

namespace SE3D
{
	DirectionalLightComponent::DirectionalLightComponent(const Vector3D& direction, float size)
		: BaseLight(Material("directional.vs", "directional.fs")), m_Direction(direction.Normalize()), m_ShadowBuffer(SE3D_SHADOW_MAP_1, SE3D_SHADOW_MAP_1), m_ShadowMaterial("directional_shadow_map.vs", "directional_shadow_map.fs"), m_Size(size)
	{
		m_DirectionNameID = String("u_direction").GetStringID();

		m_ProjectionNameID = String("u_projection").GetStringID();
		m_ViewNameID = String("u_view").GetStringID();
		m_ModelNameID = String("u_model").GetStringID();
		m_ShadowMapNameID = String("u_shadow_map").GetStringID();
	}

	void DirectionalLightComponent::Init() {}
	void DirectionalLightComponent::Input(float DeltaTime) {}
	void DirectionalLightComponent::Update(float DeltaTime) {}

	void DirectionalLightComponent::Render(DeferredRenderer* renderer)
	{
		renderer->AddLight(*this);
		m_Material.SetParamVector3D(m_DirectionNameID, m_Direction);
		m_Material.SetParamVector3D(m_ColorNameID, m_Color);
		m_Material.SetParamFloat(m_IntensityNameID, m_Intensity);

		m_View = Matrix4D::LookAt(Vector3D(), m_Direction, Vector3D(0, 1, 0));

		m_Projection = Matrix4D::Orthographic(-m_Size, m_Size, -m_Size, m_Size, -m_Size, m_Size);

		m_ShadowMaterial.SetParamMatrix4D(m_ProjectionNameID, m_Projection);
		m_ShadowMaterial.SetParamMatrix4D(m_ViewNameID, m_View);

		m_ShadowBuffer.Bind();
		m_ShadowBuffer.Clear();
		m_ShadowBuffer.Unbind();
	}

	void DirectionalLightComponent::RenderShadowMap(DeferredRenderer* renderer)
	{
		Graphics::GetInstance().Resize(SE3D_SHADOW_MAP_1, SE3D_SHADOW_MAP_1);
		m_ShadowBuffer.Bind();

		for (uint32 i = 0; i < renderer->GetObjectToRender()->Size(); ++i)
		{
			m_ShadowMaterial.SetParamMatrix4D(m_ModelNameID, (*renderer->GetObjectToRender())[i]->GetOwner()->GetWorldTransformMatrix());

			(*renderer->GetObjectToRender())[i]->PutOnScreen(renderer, &m_ShadowMaterial);
		}

		m_ShadowBuffer.Unbind();
		Graphics::GetInstance().Resize(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY());

		m_Material.SetParamMatrix4D(m_ProjectionNameID, m_Projection);
		m_Material.SetParamMatrix4D(m_ViewNameID, m_View);
		m_Material.SetParamTexture2D(m_ShadowMapNameID, m_ShadowBuffer.GetTexture());
	}

}
