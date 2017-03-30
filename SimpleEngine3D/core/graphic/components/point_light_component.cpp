#include "point_light_component.h"
#include "../deferred_renderer.h"

namespace SE3D
{
	PointLightComponent::PointLightComponent(const Vector3D& position)
		: BaseLight(Material("point.vs", "point.fs")), m_Position(position), m_Constant(1), m_Linear(0.09f), m_Quadratic(0.032)
	{
		m_PositionNameID = String("u_position").GetStringID();
		m_LinearID = String("u_linear").GetStringID();
		m_ConstantID = String("u_constant").GetStringID();
		m_QuadraticID = String("u_quadratic").GetStringID();
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
		m_Material.SetParamFloat(m_ConstantID, m_Constant);
		m_Material.SetParamFloat(m_LinearID, m_Linear);
		m_Material.SetParamFloat(m_QuadraticID, m_Quadratic);
	}
}
