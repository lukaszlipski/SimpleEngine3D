#pragma once
#include "../../math/matrix4d.h"
#include "component.h"

namespace SE3D
{
	class CameraComponent : public Component
	{
	private:
		Matrix4D m_Projection;

	public:
		CameraComponent(Matrix4D projection);
		Matrix4D GetView() const;
		inline Matrix4D GetProjection() const { return m_Projection; }

		void Init() override;
		void Update(float DeltaTime) override;
		void Render() override;

	};
}
