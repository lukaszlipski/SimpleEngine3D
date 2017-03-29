#pragma once
#include "gbuffer.h"
#include "game_object.h"
#include "framebuffer2d.h"
#include "material.h"
#include "components/camera_component.h"

namespace SE3D
{
	class DeferredRenderer
	{
	private:
		GBuffer m_GBuffer;
		uint32 m_ScreenVAO;
		Framebuffer2D m_ScreenBuffer;
		Material m_ScreenMaterial;
		CameraComponent *m_MainCamera;

	public:
		DeferredRenderer();
		void Render(GameObject *scene, CameraComponent *mainCamera);

		inline CameraComponent *GetCamera() const { return m_MainCamera; }

	};
}
