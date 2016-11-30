//if Windows
#include <Windows.h>

#include "system/window.h"
#include "system/timer.h"
#include "system/file.h"
#include "utilities/image.h"
#include "graphic/shader.h"
#include "utilities/assertion.h"

// debug
#include <stdio.h>
using namespace SE3D;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window win;

	win.Init("Lukasz Lipski : SimpleEngine3D",1024,720,hInstance);
	Timer timer;
	//Image img("C:/Programowanie/CPP/testps.bmp");

	win.SetCursor(true);
	win.SetFullScreen(false);
	//win.SetWindowSize(800, 600);

	// ---------- TEST OPENGL INIT --------------
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	Shader test("C:/Programowanie/CPP/SimpleEngine3D/SimpleEngine3D/core/graphic/shaders/shader.vs", "C:/Programowanie/CPP/SimpleEngine3D/SimpleEngine3D/core/graphic/shaders/shader.fs");

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glUseProgram(sProgram);

	// -------------------------------------------

	
	timer.Init();
	while (!win.ShouldWindowClose())
	{
		win.Clear();
		win.ProcessInput();

		if (win.GetMouseButton(0))
			OutputDebugString("!");

		char Buffer[256];
		sprintf_s(Buffer,"TimeElapsed: %f\n",timer.TimeSEC());
		OutputDebugString(Buffer);

		short x = win.GetMousePositionX();
		short y = win.GetMousePositionY();

		// ---------- TEST OPENGL UPDATE --------------
		test.Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		test.Unbind();
		// -------------------------------------------


		win.SwapBuffers();
		timer.Update();
	}

	win.Terminate();

	return EXIT_SUCCESS;
}