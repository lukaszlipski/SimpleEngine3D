#include "deferred_renderer.h"
#include "../system/graphics.h"
#include "../system/window.h"

namespace SE3D
{

	DeferredRenderer::DeferredRenderer()
		: m_GBuffer(new GBuffer()), m_ScreenMaterial("screen.vs", "screen.fs"),m_BloomMaterial("bloom.vs","bloom.fs"), m_Gaussian("gaussian.vs", "gaussian.fs"), m_MainCamera(nullptr), m_Scene(nullptr)
	{

		TextureSettings texSettings;
		texSettings.m_Format = ImageFormat::RGBA;
		texSettings.m_InternalFormat = InternalFormat::RGBA32F;
		texSettings.m_ImageType = ImageType::FLOAT;
		texSettings.m_TextureFilter = TextureFilter::LINEAR;
		texSettings.m_TextureWrap = TextureWrap::CLAMP_TO_EDGE;

		m_ScreenBuffer = new Framebuffer2D(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY(),texSettings);

		// Bloom
		m_BloomBuffer = new Framebuffer2D(static_cast<int32>(Graphics::GetInstance().GetResolutionX()/2.0f), static_cast<int32>(Graphics::GetInstance().GetResolutionY()/2.0f), texSettings);
		m_GaussianPass[0] = new Framebuffer2D(static_cast<int32>(Graphics::GetInstance().GetResolutionX()/3.0f), static_cast<int32>(Graphics::GetInstance().GetResolutionY()/3.0f), texSettings);
		m_GaussianPass[1] = new Framebuffer2D(static_cast<int32>(Graphics::GetInstance().GetResolutionX()/3.0f), static_cast<int32>(Graphics::GetInstance().GetResolutionY()/3.0f), texSettings);
		m_PassNameID = String("u_pass").GetStringID();
		m_BloomNameID = String("u_bloomTexture").GetStringID();
		m_GaussianPassesCount = 10;

		m_ScreenTexNameID = String("u_screenTexture").GetStringID();
		m_CameraPositionNameID = String("u_cameraPosition").GetStringID();
		m_PositionBufferNameID = String("u_positionTexture").GetStringID();
		m_NormalBufferNameID = String("u_normalTexture").GetStringID();
		m_AlbedoNameID = String("u_albedoTexture").GetStringID();
		u_MetallicRoughnessAONameID = String("u_metallicRoughnessAOTexture").GetStringID();

		// --------------------- RAW OPENGL ---------------------
		GLfloat quad[] = {
			-1.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f,

			-1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		};

		GLuint quadVBO;
		glGenVertexArrays(1, &m_ScreenVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(m_ScreenVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
		glBindVertexArray(0);
		// ---------------------------------------------------------
	}

	void DeferredRenderer::Render(GameObject& scene, CameraComponent &mainCamera)
	{
		
		m_MainCamera = &mainCamera;
		m_Scene = &scene;

		m_Scene->Render(this);

		ShadowPhase();

		GBufferPhase();
			
		LightPhase();

		BloomPhase();

		Graphics::GetInstance().Clear();
		Graphics::GetInstance().Resize(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());

		
		m_ScreenMaterial.Bind();
		glBindVertexArray(m_ScreenVAO);
		Graphics::GetInstance().SetDepthBuffer(false);

		m_ScreenMaterial.SetParamTexture2D(m_ScreenTexNameID, m_ScreenBuffer->GetTexture());
		m_ScreenMaterial.SetParamTexture2D(m_BloomNameID, m_GaussianPass[(m_GaussianPassesCount - 1) % 2]->GetTexture());
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		m_ScreenMaterial.Unbind();

		m_Lights.Clear();
		m_ObjectsToRender.Clear();
		
	}

	void DeferredRenderer::ShadowPhase()
	{
		Graphics::GetInstance().SetDepthBuffer(true);
		Graphics::GetInstance().SetFaceCulling(0);
		for (uint32 i = 0; i < m_Lights.Size(); ++i)
		{
			m_Lights[i]->RenderShadowMap(this);
		}
		Graphics::GetInstance().SetFaceCulling(1);
	}

	void DeferredRenderer::GBufferPhase()
	{
		if (Graphics::GetInstance().GetResolutionY() != m_GBuffer->GetHeight() || Graphics::GetInstance().GetResolutionX() != m_GBuffer->GetWidth())
		{
			delete m_GBuffer;
			m_GBuffer = new GBuffer();
		}

		m_GBuffer->Bind();
		m_GBuffer->Clear();
		Graphics::GetInstance().SetDepthBuffer(true);
		Graphics::GetInstance().Resize(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY());

		for (uint32 i = 0; i < m_ObjectsToRender.Size(); ++i)
		{
			if (m_MainCamera->GetFrustum().IsSphereInFrustum(m_ObjectsToRender[i]->GetFrustumCollision()))
			{
				m_ObjectsToRender[i]->PutOnScreen(this);
			}
		}

		m_GBuffer->Unbind();
	}

	void DeferredRenderer::LightPhase()
	{
		if (Window::GetInstance().GetSizeX() != m_ScreenBuffer->GetWidth() || Window::GetInstance().GetSizeY() != m_ScreenBuffer->GetHeight())
		{
			delete m_ScreenBuffer;
			m_ScreenBuffer = new Framebuffer2D(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(false);
		glDepthFunc(GL_EQUAL);

		m_ScreenBuffer->Bind();
		m_ScreenBuffer->Clear();

		Graphics::GetInstance().Resize(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());

		for(uint32 i=0;i<m_Lights.Size();++i)
		{

			m_Lights[i]->GetMaterial().SetParamTexture2D(m_PositionBufferNameID, m_GBuffer->GetPositionBuffer());
			m_Lights[i]->GetMaterial().SetParamTexture2D(m_NormalBufferNameID, m_GBuffer->GetNormalBuffer());
			m_Lights[i]->GetMaterial().SetParamTexture2D(m_AlbedoNameID, m_GBuffer->GetAlbedoBuffer());
			m_Lights[i]->GetMaterial().SetParamTexture2D(u_MetallicRoughnessAONameID, m_GBuffer->GetMetallicRoughnessAOBuffer());
			m_Lights[i]->GetMaterial().Bind();

			glBindVertexArray(m_ScreenVAO);
			Graphics::GetInstance().SetDepthBuffer(false);
			
			m_Lights[i]->GetMaterial().SetParamVector3D(m_CameraPositionNameID, m_MainCamera->GetPosition());
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);

			m_Lights[i]->GetMaterial().Unbind();
		}

		m_ScreenBuffer->Unbind();

		glDepthFunc(GL_LESS);
		glDepthMask(true);
		glDisable(GL_BLEND);
	}

	void DeferredRenderer::BloomPhase()
	{
		Graphics::GetInstance().Resize(static_cast<int32>(Graphics::GetInstance().GetResolutionX()/2.0f), static_cast<int32>(Graphics::GetInstance().GetResolutionY()/2.0f));

		m_BloomBuffer->Clear();
		Graphics::GetInstance().SetDepthBuffer(false);
		m_BloomBuffer->Bind();

		m_BloomMaterial.Bind();
		m_ScreenBuffer->GetTexture().Bind(0);

		glBindVertexArray(m_ScreenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		m_BloomMaterial.Unbind();
		m_BloomBuffer->Unbind();

		Graphics::GetInstance().Resize(static_cast<int32>(Graphics::GetInstance().GetResolutionX() / 3.0f), static_cast<int32>(Graphics::GetInstance().GetResolutionY() / 3.0f));
		for (uint32 i = 0; i < m_GaussianPassesCount; ++i)
		{
			int32 pass = (i % 2);
			m_GaussianPass[pass]->Bind();
			m_Gaussian.Bind();

			m_Gaussian.SetParamInt32(m_PassNameID, pass);
			if (!i)
			{
				m_BloomBuffer->GetTexture().Bind(0);
			}
			else
			{
				m_GaussianPass[!pass]->GetTexture().Bind(0);
			}


			glBindVertexArray(m_ScreenVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);

			m_Gaussian.Unbind();
			m_GaussianPass[pass]->Unbind();
		}

		Graphics::GetInstance().SetDepthBuffer(true);

		Graphics::GetInstance().Resize(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY());
	}
}
