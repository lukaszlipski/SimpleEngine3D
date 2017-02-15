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
#include "system/resource_manager.h"
#include "utilities/debug_msg.h"

// debug
#include <stdio.h>

using namespace SE3D;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	File::GetInstance().Startup();
	Window::GetInstance().Startup("Lukasz Lipski : SimpleEngine3D", 1024, 720, hInstance);
	Graphics::GetInstance().Startup();
	Input::GetInstance().Startup();
	GlobalTimer::GetInstance().Startup();
	ResourceManager::GetInstance().Startup();

	//Image img("C:/Programowanie/CPP/testps.bmp");
	//OBJLoader a("C:/Programowanie/CPP/monkeyTriangulate.obj");

	FPSCamera TestCamera(Matrix4D::Perspective(45.0f, (float)Window::GetInstance().GetSizeX() / (float)Window::GetInstance().GetSizeY(), 0.1f, 100.0f), Vector3D(0, 0, -3));

	// ---------- TEST OPENGL INIT --------------
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	Material mat("C:/Programowanie/CPP/SimpleEngine3D/SimpleEngine3D/core/graphic/shaders/shader.vs", "C:/Programowanie/CPP/SimpleEngine3D/SimpleEngine3D/core/graphic/shaders/shader.fs");

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// -------------------------------------------

	GlobalTimer::GetInstance().Reset();
	while (!Window::GetInstance().ShouldWindowClose())
	{
		Graphics::GetInstance().Clear();
		Input::GetInstance().Update();

		DebugOutputMSG("TimeElapsed: %fs\n", static_cast<float>(GlobalTimer::GetInstance().TimeSEC()));


		TestCamera.Update();
		// ---------- TEST OPENGL UPDATE --------------
		mat.Bind();

		Matrix4D model = Matrix4D::Identity();

		mat.SetParamMatrix4D(String("u_model").GetStringID(), model);
		mat.SetParamMatrix4D(String("u_view").GetStringID(), TestCamera.GetView());
		mat.SetParamMatrix4D(String("u_projection").GetStringID(), TestCamera.GetProjection());

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		mat.Unbind();
		// -------------------------------------------


		Graphics::GetInstance().Update();
		GlobalTimer::GetInstance().Update();
	}

	ResourceManager::GetInstance().Shutdown();
	GlobalTimer::GetInstance().Shutown();
	Input::GetInstance().Shutown();
	Graphics::GetInstance().Shutdown();
	Window::GetInstance().Shutdown();
	File::GetInstance().Shutdown();

	return EXIT_SUCCESS;
}
