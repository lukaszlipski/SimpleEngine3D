#pragma once
#include "../math/vector3d.h"
#include "../material.h"

namespace SE3D
{
	class DeferredRenderer;

	class BaseLight
	{
	protected:
		Material m_Material;
		Vector3D m_Color;
		float m_Intensity;
		uint32 m_ColorNameID;
		uint32 m_IntensityNameID;

	public:
		BaseLight(const Material& material) : m_Material(material), m_Color(Vector3D(1, 1, 1)), m_Intensity(1.0f)
		{
			m_ColorNameID = String("u_color").GetStringID();
			m_IntensityNameID = String("u_intensity").GetStringID();
		}
		
		inline Material& GetMaterial() { return m_Material; }
		inline void SetColor(Vector3D color) { m_Color = color; }
		inline Vector3D GetColor() const { return m_Color; }
		inline void SetIntensity(float intensity) { m_Intensity = intensity; }
		inline float GetIntensity() const { return m_Intensity; }

		virtual void RenderShadowMap(DeferredRenderer* renderer) = 0;

	};
}
