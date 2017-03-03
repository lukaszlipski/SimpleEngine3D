//if Windows
#include <Windows.h>

#include "utilities/types.h"
#include "system/window.h"
#include "system/graphics.h"
#include "system/input.h"
#include "system/global_timer.h"
#include "system/file.h"
#include "utilities/image.h"
#include "graphic/shader.h"
#include "utilities/assertion.h"
#include "math/math.h"
#include "containers/dynamic_array.h"
#include "utilities/obj_loader.h"
#include "utilities/string.h"
#include "graphic/camera/fps_camera.h"
#include "graphic/material.h"
#include "system/shader_manager.h"
#include "utilities/debug_msg.h"
#include "system/texture_manager.h"
#include "graphic/mesh.h"
#include "graphic/model.h"

using namespace SE3D;

int main()
{
	File::GetInstance().Startup();
	Window::GetInstance().Startup();
	Graphics::GetInstance().Startup();
	Input::GetInstance().Startup();
	GlobalTimer::GetInstance().Startup();
	ShaderManager::GetInstance().Startup();
	TextureManager::GetInstance().Startup();

	Model model("resources/models/test.obj");
	model.GetModel(0)->GetMaterial().SetParamVector3D(String("u_color").GetStringID(), Vector3D(1, 0, 0));
	model.GetModel(1)->GetMaterial().SetParamVector3D(String("u_color").GetStringID(), Vector3D(0, 1, 0));
	model.GetModel(2)->GetMaterial().SetParamVector3D(String("u_color").GetStringID(), Vector3D(0, 0, 1));

	float time = 0.0f;

	// --------------------- TEST OPENGL ---------------------
	GLfloat quad[] = {  
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	GLuint quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));
	glBindVertexArray(0);

	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	Texture2D screenTexture(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture.GetTextureID(), 0);
	
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return -1;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Shader screenShr("resources/shaders/screen.vs", "resources/shaders/screen.fs");
	// ---------------------------------------------------------

	FPSCamera TestCamera(Matrix4D::Perspective(45.0f, (float)Window::GetInstance().GetSizeX() / (float)Window::GetInstance().GetSizeY(), 0.1f, 100.0f), Vector3D(0, 0, -3));

	GlobalTimer::GetInstance().Reset();
	while (!Window::GetInstance().ShouldWindowClose())
	{
		//Graphics::GetInstance().Clear();
		Input::GetInstance().Update();

		DebugOutputMSG("TimeElapsed: %fs\n", static_cast<float>(GlobalTimer::GetInstance().DeltaTime()));

		TestCamera.Update();

		time += GlobalTimer::GetInstance().DeltaTime();

		Matrix4D transform = Matrix4D::Identity();
		transform = transform.Rotate(time * 10,Vector3D(0,1,0)).Scale(Vector3D(0.5f, 0.5f, 0.5f));

		model.SetTransformation(transform);
		for (uint32 i = 0; i < model.GetMeshesSize(); i++)
		{
			model.GetModel(i)->GetMaterial().SetParamMatrix4D(String("u_view").GetStringID(), TestCamera.GetView());
			model.GetModel(i)->GetMaterial().SetParamMatrix4D(String("u_projection").GetStringID(), TestCamera.GetProjection());
		}
		
		// --------------------- TEST OPENGL ---------------------
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		Graphics::GetInstance().Clear();
		Graphics::GetInstance().SetDepthBuffer(true);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		model.Draw();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0, 0, 0, 1);
		
		screenShr.Bind();
		glBindVertexArray(quadVAO);
		Graphics::GetInstance().SetDepthBuffer(false);
		
		glBindTexture(GL_TEXTURE_2D, screenTexture.GetTextureID());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		screenShr.Unbind();
		// ---------------------------------------------------------
		//model.Draw();

		if (Input::GetInstance().GetKey(SE3D_ESCAPE))
			Window::GetInstance().CloseWindow();

		Graphics::GetInstance().Update();
		GlobalTimer::GetInstance().Update();
	}

	TextureManager::GetInstance().Shutdown();
	ShaderManager::GetInstance().Shutdown();
	GlobalTimer::GetInstance().Shutown();
	Input::GetInstance().Shutown();
	Graphics::GetInstance().Shutdown();
	Window::GetInstance().Shutdown();
	File::GetInstance().Shutdown();

	return 0;
}
