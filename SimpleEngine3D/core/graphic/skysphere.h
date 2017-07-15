#pragma once
#include "texture2d.h"
#include "material.h"
#include "model.h"

namespace SE3D
{
	class DeferredRenderer;

	class Skysphere 
	{
	private:
		Texture2D* m_Texture;
		Material m_Material;
		Model m_Sphere;
		uint32 m_SkysphereTextureNameID;

	public:
		Skysphere(String path, bool srgb);
		void Draw(DeferredRenderer* renderer);

	};
}