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
#include "math/frustum.h"
#include "math/sphere.h"

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

	Model model("resources/models/cube.obj");
	model.GetMesh(0)->GetMaterial().SetParamTexture2D(String("u_albedo").GetStringID(), "brick1/albedo.bmp",true);
	model.GetMesh(0)->GetMaterial().SetParamTexture2D(String("u_normal").GetStringID(), "brick1/normal.bmp");
	model.GetMesh(0)->GetMaterial().SetParamTexture2D(String("u_roughness").GetStringID(), "brick1/roughness.bmp");
	model.GetMesh(0)->GetMaterial().SetParamTexture2D(String("u_ambientOcclusion").GetStringID(), "brick1/ao.bmp");
	model.GetMesh(0)->GetMaterial().SetParamTexture2D(String("u_height").GetStringID(), "brick1/height.bmp");
	model.GetMesh(0)->GetMaterial().SetParamFloat(String("u_heightScale").GetStringID(), 0.06f);
	
	Model model2("resources/models/cube.obj");
	model2.GetMesh(0)->GetMaterial().SetParamTexture2D(String("u_albedo").GetStringID(), "aluminum/albedo.bmp", true);
	model2.GetMesh(0)->GetMaterial().SetParamTexture2D(String("u_metallic").GetStringID(), "aluminum/metallic.bmp");
	model2.GetMesh(0)->GetMaterial().SetParamTexture2D(String("u_roughness").GetStringID(), "aluminum/roughness.bmp");

	//Window::GetInstance().SetFullScreen(true);
	Graphics::GetInstance().SetResolution(1366, 768);
	Window::GetInstance().SetSize(1366, 768);

	GameObject root;

	GameObject child;
	ModelComponent modelComp2(model2);
	child.AddComponent(modelComp2);
	child.SetPosition(Vector3D(1.5f, 0, 0));
	child.SetScale(Vector3D(0.5f, 0.5f, 0.5f));
	root.AddChild(child);

	GameObject child2;
	ModelComponent modelComp(model);
	child2.SetScale(Vector3D(0.5f, 0.5f, 0.5f));
	child2.AddComponent(modelComp);
	root.AddChild(child2);

	PointLightComponent pointLComp(Vector3D(2.0f, 2.0f, 2.0f));
	root.AddComponent(pointLComp);
	DirectionalLightComponent dirLComp(Vector3D(-1, -1, -1));
	dirLComp.SetIntensity(0.8f);
	root.AddComponent(dirLComp);
	//SpotLightComponent spotLComp(Vector3D(1.5f, 0, 2), Vector3D(0, 0, -1));
	//root.AddComponent(spotLComp);
	
	GameObject cameraChild;
	CameraComponent cameraComp(Frustum(45.0f, static_cast<float>(Graphics::GetInstance().GetResolutionX()) / static_cast<float>(Graphics::GetInstance().GetResolutionY()), 0.01f, 100.0f));
	MovementComponent movementComp(3.0f,5.0f);
	cameraChild.AddComponent(cameraComp);
	cameraChild.AddComponent(movementComp);
	cameraChild.SetPosition(Vector3D(0.7f, 0, 3));
	cameraChild.SetRotation(Quaternion(Vector3D(0, 1, 0), 0));
	root.AddChild(cameraChild);
	
	root.Init();

	DeferredRenderer renderer;

	float time = 0.0f;

	GlobalTimer::GetInstance().Reset();
	while (!Window::GetInstance().ShouldWindowClose())
	{
		Input::GetInstance().Update();

		root.Input(GlobalTimer::GetInstance().DeltaTime());
		root.Update(GlobalTimer::GetInstance().DeltaTime());

		//DebugOutputMSG("TimeElapsed: %fs\n", static_cast<float>(GlobalTimer::GetInstance().DeltaTime()));


		time += GlobalTimer::GetInstance().DeltaTime();

		//child.SetRotation(Quaternion(Vector3D(0, 1, 0), time * 5));
		//child2.SetRotation(Quaternion(Vector3D(0, 1, 0), time * 5));
		
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
