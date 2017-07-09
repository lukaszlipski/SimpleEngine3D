#include "frustum.h"
#include "math.h"

namespace SE3D
{
	Frustum::Frustum(float angle, float ratio, float np, float fp)
		: m_Angle(angle), m_Ratio(ratio), m_NearPlane(np), m_FarPlane(fp)
	{
		m_Tangens = static_cast<float>(Tan(ToRadians(angle) * 0.5f));
	}

	void Frustum::UpdateCameraFrustum(const Vector3D& pos, const Vector3D& forward, const Vector3D& right)
	{
		Vector3D f = forward.Normalize();
		Vector3D s = right.Normalize();
		Vector3D u(s.Cross(f));

		// near plane
		m_Planes[0].point = pos + f * m_NearPlane;
		m_Planes[0].normal = f;

		// far plane
		m_Planes[1].point = pos + f * m_FarPlane;
		m_Planes[1].normal = f * -1;

		// top plane
		m_Planes[2].point = m_Planes[0].point + u * m_NearPlane * m_Tangens;
		m_Planes[2].normal = (m_Planes[2].point - pos).Normalize().Cross(s);

		// bottom plane
		m_Planes[3].point = m_Planes[0].point - u * m_NearPlane * m_Tangens;
		m_Planes[3].normal = s.Cross((m_Planes[3].point - pos).Normalize());

		// left plane
		m_Planes[4].point = m_Planes[0].point - s * m_NearPlane * m_Tangens * m_Ratio;
		m_Planes[4].normal = (m_Planes[4].point - pos).Normalize().Cross(u);

		// right plane
		m_Planes[5].point = m_Planes[0].point + s * m_NearPlane * m_Tangens * m_Ratio;
		m_Planes[5].normal = u.Cross((m_Planes[5].point - pos).Normalize());

	}

	bool Frustum::IsSphereInFrustum(const Sphere& sphere)
	{
		for (Plane& p : m_Planes)
		{
			float distance = p.Distance(sphere.center);
			if (distance < -sphere.radius) { return false; }
		}
		return true;
	}

}