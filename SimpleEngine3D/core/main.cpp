//if Windows
#include <Windows.h>

#include "system/window.h"
#include "system/timer.h"
#include "system/file.h"
#include "utilities/image.h"

// debug
#include <stdio.h>
using namespace SE3D;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Window win;

	win.Init("Lukasz Lipski : SimpleEngine3D",1024,720,hInstance);
	Timer timer;
	//IMAGE img = Image::LoadBMP("C:/Programowanie/CPP/test.bmp");
	//Image::Delete(img);

	win.SetCursor(true);
	win.SetFullScreen(false);
	//win.SetWindowSize(800, 600);

	// ---------- TEST OPENGL INIT --------------
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	const char* testVSSource = "#version 330 core\n layout (location = 0) in vec3 position;\n void main()\n {\n gl_Position = vec4(position.x, position.y, position.z, 1.0);\n }\0";
	const char* testFSSource = "#version 330 core\n out vec4 color;\n void main()\n {\n color = vec4(0.66f, 0, 1.0f, 1.0f);\n }\n\0";

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &testVSSource, NULL);
	glCompileShader(vShader);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &testFSSource, NULL);
	glCompileShader(fShader);
	GLuint sProgram = glCreateProgram();
	glAttachShader(sProgram, vShader);
	glAttachShader(sProgram, fShader);
	glLinkProgram(sProgram);
	glDeleteShader(vShader);
	glDeleteShader(fShader);

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
	glUseProgram(sProgram);

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
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		// -------------------------------------------


		win.SwapBuffers();
		timer.Update();
	}

	win.Terminate();

	return EXIT_SUCCESS;
}