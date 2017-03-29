#include "deferred_renderer.h"
#include "../system/graphics.h"
#include "../system/window.h"

namespace SE3D
{
	DeferredRenderer::DeferredRenderer()
		: m_ScreenBuffer(Framebuffer2D(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY())), m_ScreenMaterial("screen.vs", "screen.fs")
	{

		// --------------------- RAW OPENGL ---------------------
		GLfloat quad[] = {
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			1.0f, -1.0f,  1.0f, 0.0f,
			1.0f,  1.0f,  1.0f, 1.0f
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

	void DeferredRenderer::Render(GameObject* scene, CameraComponent *mainCamera)
	{
		
		m_MainCamera = mainCamera;

		if(Graphics::GetInstance().GetResolutionY() != m_GBuffer.GetHeight() || Graphics::GetInstance().GetResolutionX() != m_ScreenBuffer.GetWidth())
			m_GBuffer = GBuffer();
			
		if(Window::GetInstance().GetSizeX() != m_ScreenBuffer.GetWidth() || Window::GetInstance().GetSizeY() != m_ScreenBuffer.GetHeight())
			m_ScreenBuffer = Framebuffer2D(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());

		m_GBuffer.Bind();
		m_GBuffer.Clear();
		Graphics::GetInstance().SetDepthBuffer(true);
		Graphics::GetInstance().Resize(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY());
		
		scene->Render(this);

		m_GBuffer.Unbind();

		Graphics::GetInstance().Clear();
		Graphics::GetInstance().Resize(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());

		m_ScreenMaterial.Bind();
		// --------------------- RAW OPENGL ---------------------
		glBindVertexArray(m_ScreenVAO);
		// ---------------------------------------------------------
		Graphics::GetInstance().SetDepthBuffer(false);

		m_GBuffer.GetNormalBuffer().Bind(0);
		// --------------------- RAW OPENGL ---------------------
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		// ---------------------------------------------------------
		m_ScreenMaterial.Unbind();
	}
}
