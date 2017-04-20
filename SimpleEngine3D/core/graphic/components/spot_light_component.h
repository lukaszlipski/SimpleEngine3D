#pragma once
#include "base_light.h"
#include "component.h"

namespace SE3D
{
	class SpotLightComponent : public BaseLight, public Component
	{
	private:
		Vector3D m_Position;
		Vector3D m_Direction;
		float m_CutOff;
		float m_CutOffOut;
		float m_Radius;
		uint32 m_RadiusNameID;
		uint32 m_PositionNameID;
		uint32 m_DirectionNameID;
		uint32 m_CutOffNameID;
		uint32 m_CutOffOutNameID;

	public:
		SpotLightComponent(const Vector3D& position = Vector3D(0,0,0), const Vector3D& direction = Vector3D(0,-1,0), float radius = 5.0f, float cutOff = 12.0f, float cutOffOut = 17.0f);

		inline void SetPosition(const Vector3D& pos) { m_Position = pos; }
		inline Vector3D GetPosition() const { return m_Position; }
		inline void SetDirection(const Vector3D& dir) { m_Direction = dir.Normalize(); }
		inline Vector3D GetDirection() const { return m_Direction; }
		inline void SetCutOff(float cutOff) { m_CutOff = cutOff; }
		inline float GetCutOff() const { return m_CutOff; }
		inline void SetCutOffOuter(float cof) { m_CutOffOut = cof; }
		inline float GetCutOffOuter() const { return m_CutOffOut; }

		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer* renderer) override;

	private:
		void SetParams();
	};
}