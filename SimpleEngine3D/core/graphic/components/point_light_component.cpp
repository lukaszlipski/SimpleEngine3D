#include "point_light_component.h"
#include "../deferred_renderer.h"

namespace SE3D
{
	PointLightComponent::PointLightComponent(const Vector3D& position, float radius)
		: BaseLight(Material("point.vs", "point.fs")), m_Position(position), m_Radius(radius)
	{
		m_PositionNameID = String("u_position").GetStringID();
		m_RadiusNameID = String("u_radius").GetStringID();
		SetParams();
	}

	void PointLightComponent::Init() {}
	void PointLightComponent::Input(float DeltaTime) {}
	void PointLightComponent::Update(float DeltaTime) {}

	void PointLightComponent::Render(DeferredRenderer* renderer)
	{
		renderer->AddLight(*this);
		m_Material.SetParamVector3D(m_PositionNameID, m_Position + m_Owner->GetPosition());
	}

	void PointLightComponent::SetParams()
	{
		m_Material.SetParamVector3D(m_ColorNameID, m_Color);
		m_Material.SetParamFloat(m_IntensityNameID, m_Intensity);
		m_Material.SetParamFloat(m_RadiusNameID, m_Radius);
	}
}
