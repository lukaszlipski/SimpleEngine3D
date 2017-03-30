#include "directional_light_component.h"
#include "../deferred_renderer.h"

namespace SE3D
{
	DirectionalLightComponent::DirectionalLightComponent(const Vector3D& direction)
		: BaseLight(Material("directional.vs", "directional.fs")), m_Direction(direction)
	{
		m_DirectionNameID = String("u_direction").GetStringID();
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
	}
}
