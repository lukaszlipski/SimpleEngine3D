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

	//Image img("C:/Programowanie/CPP/testps.bmp");
	//OBJLoader a("C:/Programowanie/CPP/monkeyTriangulate.obj");

	//Window::GetInstance().SetCursor(true);
	Window::GetInstance().SetFullScreen(false);
	//Window::GetInstance().SetWindowSize(800, 600);

	FPSCamera TestCamera(Matrix4D::Perspective(45.0f, (float)Window::GetInstance().GetSizeX() / (float)Window::GetInstance().GetSizeY(), 0.1f, 100.0f),Vector3D(0,0,-3));
	TestCamera.SetPosition(Vector3D(0, 0, -3.0f));


	// ---------- TEST OPENGL INIT --------------
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	Shader test("C:/Programowanie/CPP/SimpleEngine3D/SimpleEngine3D/core/graphic/shaders/shader.vs", "C:/Programowanie/CPP/SimpleEngine3D/SimpleEngine3D/core/graphic/shaders/shader.fs");

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
	//glUseProgram(sProgram);
	
	// -------------------------------------------

	GlobalTimer::GetInstance().Reset();
	while (!Window::GetInstance().ShouldWindowClose())
	{
		Graphics::GetInstance().Clear();
		Input::GetInstance().Update();

		if (Input::GetInstance().GetMouseButton(0))
		OutputDebugString("!");

		int16 x = Input::GetInstance().GetMousePositionX();
		int16 y = Input::GetInstance().GetMousePositionY();

		char Buffer[256];
		sprintf_s(Buffer, "TimeElapsed: %f\n", (float)GlobalTimer::GetInstance().TimeSEC());
		OutputDebugString(Buffer);


		TestCamera.Update();
		// ---------- TEST OPENGL UPDATE --------------
		test.Bind();

		Matrix4D proj = TestCamera.GetProjection();
		//Matrix4D proj2 = Matrix4D::Orthographic(0.0f, -(float)Window::GetInstance().GetSizeX(), 0.0f, (float)Window::GetInstance().GetSizeY(), 0.1f, 100.0f);
		Matrix4D view = TestCamera.GetView();
		Matrix4D model = Matrix4D::Identity();
		//model2 = model2.Translate(Vector3D(100, 100, 0)).Scale(Vector3D(100, 100, 1));
		
		glUniformMatrix4fv(glGetUniformLocation(test.GetProgram(), "u_model"), 1, GL_TRUE, (GLfloat*)model.GetPtr());
		glUniformMatrix4fv(glGetUniformLocation(test.GetProgram(), "u_view"), 1, GL_TRUE, (GLfloat*)view.GetPtr());
		glUniformMatrix4fv(glGetUniformLocation(test.GetProgram(), "u_projection"), 1, GL_TRUE, (GLfloat*)proj.GetPtr());

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		test.Unbind();
		// -------------------------------------------


		Graphics::GetInstance().Update();
		GlobalTimer::GetInstance().Update();
	}

	GlobalTimer::GetInstance().Shutown();
	Input::GetInstance().Shutown();
	Graphics::GetInstance().Shutdown();
	Window::GetInstance().Shutdown();
	File::GetInstance().Shutdown();

	return EXIT_SUCCESS;
}
