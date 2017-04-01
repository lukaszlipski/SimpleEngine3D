#include "deferred_renderer.h"
#include "../system/graphics.h"
#include "../system/window.h"

namespace SE3D
{
	DeferredRenderer::DeferredRenderer()
		: m_GBuffer(new GBuffer()), m_ScreenMaterial("screen.vs", "screen.fs"), m_MainCamera(nullptr), m_Scene(nullptr)
	{

		TextureSettings texSettings;
		texSettings.m_Format = ImageFormat::RGBA;
		texSettings.m_InternalFormat = InternalFormat::RGBA32F;
		texSettings.m_ImageType = ImageType::FLOAT;
		texSettings.m_TextureFilter = TextureFilter::LINEAR;

		m_ScreenBuffer = new Framebuffer2D(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY(),texSettings);

		m_CameraPositionNameID = String("u_cameraPosition").GetStringID();
		m_PositionBufferNameID = String("u_positionTexture").GetStringID();
		m_NormalBufferNameID = String("u_normalTexture").GetStringID();
		m_AlbedoSpecularNameID = String("u_albedoSpecularTexture").GetStringID();

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

		GBufferPhase();
			
		LightPhase();

		Graphics::GetInstance().Clear();
		Graphics::GetInstance().Resize(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());

		m_ScreenMaterial.Bind();
		glBindVertexArray(m_ScreenVAO);
		Graphics::GetInstance().SetDepthBuffer(false);

		m_ScreenBuffer->GetTexture().Bind(0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		m_ScreenMaterial.Unbind();

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

		m_Scene->Render(this);

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

		for(int32 i=0;i<m_Lights.Size();i++)
		{

			m_Lights[i]->GetMaterial().SetParamTexture2D(m_PositionBufferNameID, m_GBuffer->GetPositionBuffer());
			m_Lights[i]->GetMaterial().SetParamTexture2D(m_NormalBufferNameID, m_GBuffer->GetNormalBuffer());
			m_Lights[i]->GetMaterial().SetParamTexture2D(m_AlbedoSpecularNameID, m_GBuffer->GetAlbedoAndSpecularBuffer());
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

		m_Lights.Clear();
	}
}
