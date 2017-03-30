#pragma once
#include "gbuffer.h"
#include "game_object.h"
#include "framebuffer2d.h"
#include "material.h"
#include "components/camera_component.h"
#include "components/base_light.h"

namespace SE3D
{
	class DeferredRenderer
	{
	private:
		GBuffer *m_GBuffer;
		uint32 m_ScreenVAO;
		Framebuffer2D *m_ScreenBuffer;
		Material m_ScreenMaterial;
		CameraComponent *m_MainCamera;
		GameObject *m_Scene;
		DynamicArray<BaseLight*> m_Lights;
		uint32 m_CameraPositionNameID;
		uint32 m_PositionBufferNameID;
		uint32 m_NormalBufferNameID;
		uint32 m_AlbedoSpecularNameID;

	public:
		DeferredRenderer();
		void Render(GameObject &scene, CameraComponent &mainCamera);

		inline void AddLight(BaseLight &light) { m_Lights.Push(&light); }
		inline CameraComponent *GetCamera() const { return m_MainCamera; }

	private:
		void GBufferPhase();
		void LightPhase();
	};
}
