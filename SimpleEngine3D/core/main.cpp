//if Windows
#include <Windows.h>

#include "utilities/types.h"
#include "system/window.h"
#include "system/graphics.h"
#include "system/input.h"
#include "system/timer.h"
#include "system/file.h"
#include "utilities/image.h"
#include "graphic/shader.h"
#include "utilities/assertion.h"
#include "math/math.h"
#include "containers/dynamic_array.h"
#include "utilities/obj_loader.h"
#include "utilities/string.h"

// debug
#include <stdio.h>

using namespace SE3D;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	File::GetInstance().Startup();
	Window::GetInstance().Startup("Lukasz Lipski : SimpleEngine3D", 1024, 720, hInstance);
	Graphics::GetInstance().Startup();
	Input::GetInstance().Startup();
	Timer timer;

	//Image img("C:/Programowanie/CPP/testps.bmp");
	//OBJLoader a("C:/Programowanie/CPP/monkeyTriangulate.obj");

	Window::GetInstance().SetCursor(true);
	Window::GetInstance().SetFullScreen(false);
	//Window::GetInstance().SetWindowSize(800, 600);

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


	timer.Init();
	while (!Window::GetInstance().ShouldWindowClose())
	{
		Graphics::GetInstance().Clear();
		Input::GetInstance().Update();

		if (Input::GetInstance().GetMouseButton(0))
		OutputDebugString("!");

		char Buffer[256];
		sprintf_s(Buffer, "TimeElapsed: %f\n", timer.TimeSEC());
		OutputDebugString(Buffer);

		int16 x = Input::GetInstance().GetMousePositionX();
		int16 y = Input::GetInstance().GetMousePositionY();

		// ---------- TEST OPENGL UPDATE --------------
		test.Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		test.Unbind();
		// -------------------------------------------


		Graphics::GetInstance().Update();
		timer.Update();
	}

	Input::GetInstance().Shutown();
	Graphics::GetInstance().Shutdown();
	Window::GetInstance().Shutdown();
	File::GetInstance().Shutdown();

	return EXIT_SUCCESS;
}
