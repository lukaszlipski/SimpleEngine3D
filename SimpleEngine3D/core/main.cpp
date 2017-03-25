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
#include "graphic/game_object.h"
#include "graphic/components/model_component.h"
#include "math/quaternion.h"
#include "graphic/framebuffer2d.h"
#include "graphic/components/camera_component.h"

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

	GameObject root;
	ModelComponent modelComp(model);
	root.AddComponent(modelComp);
	//root.SetScale(Vector3D(0.5, 0.5, 0.5));
	GameObject child;
	ModelComponent modelComp2(model);
	child.AddComponent(modelComp2);
	child.SetPosition(Vector3D(2, 2, 2));
	child.SetScale(Vector3D(0.5f, 0.5f, 0.5f));
	root.AddChild(child);
	root.SetPosition(Vector3D(-0.5f, 0, 0));

	CameraComponent cameraComp(Matrix4D::Perspective(45.0f, static_cast<float>(Graphics::GetInstance().GetResolutionX()) / static_cast<float>(Graphics::GetInstance().GetResolutionY()), 0.1f, 100.0f));
	GameObject cameraChild;
	cameraChild.AddComponent(cameraComp);
	cameraChild.SetPosition(Vector3D(0, 0, 5));
	cameraChild.SetRotation(Quaternion(Vector3D(0, 1, 0), 10));
	root.AddChild(cameraChild);

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
	// ---------------------------------------------------------

	Framebuffer2D screenFb(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY());
	Shader screenShr("resources/shaders/screen.vs", "resources/shaders/screen.fs");

	GlobalTimer::GetInstance().Reset();
	while (!Window::GetInstance().ShouldWindowClose())
	{
		//Graphics::GetInstance().Clear();
		Input::GetInstance().Update();

		DebugOutputMSG("TimeElapsed: %fs\n", static_cast<float>(GlobalTimer::GetInstance().DeltaTime()));

		time += GlobalTimer::GetInstance().DeltaTime();

		child.SetRotation(Quaternion(Vector3D(0, 0, 1), time * 5));
		for (uint32 i = 0; i < model.GetMeshesSize(); i++)
		{
			model.GetModel(i)->GetMaterial().SetParamMatrix4D(String("u_view").GetStringID(), cameraComp.GetView());
			model.GetModel(i)->GetMaterial().SetParamMatrix4D(String("u_projection").GetStringID(), cameraComp.GetProjection());
		}
			
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		screenFb.Bind();
		screenFb.Clear();
		Graphics::GetInstance().SetDepthBuffer(true);
		Graphics::GetInstance().Resize(Graphics::GetInstance().GetResolutionX(), Graphics::GetInstance().GetResolutionY());
		root.Render();

		screenFb.Unbind();
		Graphics::GetInstance().Clear();
		Graphics::GetInstance().Resize(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		screenShr.Bind();
		glBindVertexArray(quadVAO);
		Graphics::GetInstance().SetDepthBuffer(false);
		
		screenFb.GetTexture().Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		screenShr.Unbind();

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
