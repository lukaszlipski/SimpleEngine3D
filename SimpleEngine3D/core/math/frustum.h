#pragma once
#include "plane.h"
#include "sphere.h"

namespace SE3D
{
	struct Frustum
	{

	private:
		float m_Angle;
		float m_Ratio;
		float m_NearPlane;
		float m_FarPlane;
		float m_Tangens;
		Plane m_Planes[6];

	public:
		Frustum(float angle, float ratio, float np, float fp);

		void UpdateCameraFrustum(const Vector3D& pos, const Vector3D& forward, const Vector3D& right);
		bool IsSphereInFrustum(const Sphere& sphere);

		inline float GetAngle() const { return m_Angle; }
		inline float GetRatio() const { return m_Ratio; }
		inline float GetNearPlane() const { return m_NearPlane; }
		inline float GetFarPlane() const { return m_FarPlane; }

	};
}