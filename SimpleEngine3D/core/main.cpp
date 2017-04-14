//if Windows
#include <Windows.h>

#include "utilities/types.h"
#include "system/window.h"
#include "system/graphics.h"
#include "system/input.h"
#include "system/global_timer.h"
#include "system/file.h"
#include "math/math.h"
#include "system/shader_manager.h"
#include "utilities/debug_msg.h"
#include "system/texture_manager.h"
#include "graphic/mesh.h"
#include "graphic/model.h"
#include "graphic/game_object.h"
#include "graphic/components/model_component.h"
#include "math/quaternion.h"
#include "graphic/components/camera_component.h"
#include "graphic/components/movement_component.h"
#include "graphic/deferred_renderer.h"
#include "graphic/components/directional_light_component.h"
#include "graphic/components/point_light_component.h"
#include "graphic/components/spot_light_component.h"

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
	
	GameObject root;
	ModelComponent modelComp(model);
	root.AddComponent(modelComp);

	GameObject child;
	ModelComponent modelComp2(model);

	child.AddComponent(modelComp2);
	child.SetPosition(Vector3D(2, 2, 2));
	child.SetScale(Vector3D(0.5f, 0.5f, 0.5f));
	root.AddChild(child);

	//PointLightComponent pointLComp(Vector3D(-2, 0, 0));
	//child.AddComponent(pointLComp);
	SpotLightComponent spotLComp(Vector3D(-2, 0, 3), Vector3D(0, 0, -1),12.0f,17.0f);
	child.AddComponent(spotLComp);
	
	GameObject cameraChild;
	CameraComponent cameraComp(Matrix4D::Perspective(45.0f, static_cast<float>(Graphics::GetInstance().GetResolutionX()) / static_cast<float>(Graphics::GetInstance().GetResolutionY()), 0.01f, 100.0f));
	MovementComponent movementComp(3.0f,5.0f);
	cameraChild.AddComponent(cameraComp);
	cameraChild.AddComponent(movementComp);
	cameraChild.SetPosition(Vector3D(0, 0, 5));
	cameraChild.SetRotation(Quaternion(Vector3D(0, 1, 0), 10));
	root.AddChild(cameraChild);
	
	root.Init();

	DeferredRenderer renderer;

	float time = 0.0f;

	GlobalTimer::GetInstance().Reset();
	while (!Window::GetInstance().ShouldWindowClose())
	{
		Input::GetInstance().Update();

		root.Input(GlobalTimer::GetInstance().DeltaTime());

		DebugOutputMSG("TimeElapsed: %fs\n", static_cast<float>(GlobalTimer::GetInstance().DeltaTime()));

		time += GlobalTimer::GetInstance().DeltaTime();

		child.SetRotation(Quaternion(Vector3D(0, 0, 1), time * 5));
		
		renderer.Render(root,cameraComp);

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
