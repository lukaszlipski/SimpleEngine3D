#pragma once
#include "../../math/math.h"

namespace SE3D
{
	class Camera
	{
	protected:
		Matrix4D m_Projection;
		Vector3D m_Position;
		Vector3D m_Front;
		Vector3D m_Up;
		Vector3D m_Right;
		Vector3D m_WorldUp;

	public:

		Camera(const Matrix4D& projection, const Vector3D& position = Vector3D(0, 0, 0), const Vector3D& front = Vector3D(0, 0, -1), const Vector3D& worldUp = Vector3D(0, 1, 0))
			: m_Projection(projection), m_Position(position), m_Front(front), m_WorldUp(worldUp)
		{
			m_Right = front.Cross(worldUp).Normalize();
			m_Up = m_Right.Cross(front).Normalize();
		}

		virtual ~Camera() = default;
		virtual void Update() = 0;

		const Matrix4D& GetProjection() const { return m_Projection; }
		Matrix4D GetView() const { return Matrix4D::LookAt(m_Position, m_Position + m_Front, m_Up); }

		const Vector3D& GetPosition() const { return m_Position; }
		void SetPosition(const Vector3D& position) { m_Position = position; }
		const Vector3D& GetFront() const { return m_Front; }
		void SetFront(const Vector3D& front) { m_Front = front; }
		const Vector3D& GetUp() const { return m_Up; }
		void SetUp(const Vector3D& up) { m_Up = up; }
		const Vector3D& GetRight() const { return m_Right; }
		void SetRight(const Vector3D& right) { m_Right = right; }
		const Vector3D& GetWorldUp() const { return m_WorldUp; }
		void SetWorldUp(const Vector3D& worldUp) { m_WorldUp = worldUp; }
	};
}
