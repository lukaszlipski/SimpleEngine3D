#pragma once
#include "gbuffer.h"
#include "game_object.h"
#include "framebuffer2d.h"
#include "material.h"
#include "components/camera_component.h"
#include "components/base_light.h"
#include "components/model_component.h"

namespace SE3D
{
	class DeferredRenderer
	{
	private:
		GBuffer *m_GBuffer;
		uint32 m_ScreenVAO;
		Framebuffer2D *m_ScreenBuffer;

		// Bloom
		Framebuffer2D *m_BloomBuffer;
		Framebuffer2D *m_GaussianPass[2];
		Material m_BloomMaterial;
		Material m_Gaussian;
		uint32 m_PassNameID;
		uint32 m_BloomNameID;
		uint32 m_GaussianPassesCount;

		uint32 m_ScreenTexNameID;
		Material m_ScreenMaterial;
		CameraComponent *m_MainCamera;
		GameObject *m_Scene;
		DynamicArray<BaseLight*> m_Lights;
		uint32 m_CameraPositionNameID;
		uint32 m_PositionBufferNameID;
		uint32 m_NormalBufferNameID;
		uint32 m_AlbedoNameID;
		uint32 u_MetallicRoughnessAONameID;
		DynamicArray<ModelComponent*> m_ObjectsToRender;

	public:
		DeferredRenderer();
		void Render(GameObject &scene, CameraComponent &mainCamera);

		inline void AddLight(BaseLight &light) { m_Lights.Push(&light); }
		inline void AddObjectToRender(ModelComponent &obj) { m_ObjectsToRender.Push(&obj); }
		inline CameraComponent *GetCamera() const { return m_MainCamera; }
		inline DynamicArray<ModelComponent*> *GetObjectToRender() { return &m_ObjectsToRender; }

	private:
		void ShadowPhase();
		void GBufferPhase();
		void LightPhase();
		void BloomPhase();
	};
}
