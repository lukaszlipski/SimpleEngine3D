#include "spot_light_component.h"
#include "../deferred_renderer.h"
#include "../../math/math.h"

namespace SE3D
{
	SpotLightComponent::SpotLightComponent(const Vector3D & position, const Vector3D & direction, const float & cutOff, const float& cutOffOut)
		: BaseLight(Material("spot.vs", "spot.fs")), m_Position(position), m_Direction(direction), m_CutOff(ToRadians(cutOff)),m_CutOffOut(ToRadians(cutOffOut)), m_Constant(1), m_Linear(0.09f), m_Quadratic(0.032f)
	{
		m_PositionNameID = String("u_position").GetStringID();
		m_DirectionNameID = String("u_direction").GetStringID();
		m_CutOffNameID = String("u_cutOff").GetStringID();
		m_CutOffOutNameID = String("u_cutOffOut").GetStringID();
		m_LinearID = String("u_linear").GetStringID();
		m_ConstantID = String("u_constant").GetStringID();
		m_QuadraticID = String("u_quadratic").GetStringID();
		SetParams();
	}

	void SpotLightComponent::Init() {}
	void SpotLightComponent::Input(float DeltaTime) {}
	void SpotLightComponent::Update(float DeltaTime) {}

	void SpotLightComponent::Render(DeferredRenderer * renderer)
	{
		renderer->AddLight(*this);
		m_Material.SetParamVector3D(m_PositionNameID, m_Position + m_Owner->GetPosition());
		m_Material.SetParamVector3D(m_DirectionNameID, m_Direction);
		m_Material.SetParamFloat(m_CutOffNameID, cos(m_CutOff));
		m_Material.SetParamFloat(m_CutOffOutNameID, cos(m_CutOffOut));
	}

	void SpotLightComponent::SetParams()
	{
		m_Material.SetParamVector3D(m_ColorNameID, m_Color);
		m_Material.SetParamFloat(m_IntensityNameID, m_Intensity);
		m_Material.SetParamFloat(m_ConstantID, m_Constant);
		m_Material.SetParamFloat(m_LinearID, m_Linear);
		m_Material.SetParamFloat(m_QuadraticID, m_Quadratic);
	}
}