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
	float time = 0.0f;

	FPSCamera TestCamera(Matrix4D::Perspective(45.0f, (float)Window::GetInstance().GetSizeX() / (float)Window::GetInstance().GetSizeY(), 0.1f, 100.0f), Vector3D(0, 0, -3));

	GlobalTimer::GetInstance().Reset();
	while (!Window::GetInstance().ShouldWindowClose())
	{
		Graphics::GetInstance().Clear();
		Input::GetInstance().Update();

		DebugOutputMSG("TimeElapsed: %fs\n", static_cast<float>(GlobalTimer::GetInstance().TimeSEC()));

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

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		model.Draw();

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
