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

	OBJLoader a("resources/models/test.obj");

	FPSCamera TestCamera(Matrix4D::Perspective(45.0f, (float)Window::GetInstance().GetSizeX() / (float)Window::GetInstance().GetSizeY(), 0.1f, 100.0f), Vector3D(0, 0, -3));

	Material mat("default.vs", "default.fs");
	mat.SetTexture2D(String("u_texture").GetStringID(), "gradTest.bmp");
	mat.SetTexture2D(String("u_tex").GetStringID(), "texTest.bmp");

	// ---------- TEST OPENGL INIT --------------

	GLuint VBO, VAO, IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, a.GetMesh(2)->m_Vertices.Size() * sizeof(Vector3D), &a.GetMesh(2)->m_Vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, a.GetMesh(2)->m_Indices.Size() * sizeof(GLuint), &a.GetMesh(2)->m_Indices[0], GL_STATIC_DRAW);
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
		model = model.Scale(Vector3D(0.2f, 0.2f, 0.2f));

		mat.SetParamMatrix4D(String("u_model").GetStringID(), model);
		mat.SetParamMatrix4D(String("u_view").GetStringID(), TestCamera.GetView());
		mat.SetParamMatrix4D(String("u_projection").GetStringID(), TestCamera.GetProjection());

		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, a.GetMesh(2)->m_Indices.Size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		mat.Unbind();
		// -------------------------------------------

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

	return EXIT_SUCCESS;
}
