#include "model_component.h"
#include "../deferred_renderer.h"

namespace SE3D
{

	ModelComponent::ModelComponent(Model& model)
	{
		m_Model = &model;
	}

	void ModelComponent::Init() {}
	void ModelComponent::Input(float DeltaTime) {}
	void ModelComponent::Update(float DeltaTime) {}

	void ModelComponent::Render(DeferredRenderer *renderer)
	{
		m_FrustumCollision = Sphere(m_Owner->GetWorldTransform().Position,
									( Vector3D(m_Owner->GetWorldTransform().Scale.x * m_Model->GetFurthestLocalPoint().x,
										m_Owner->GetWorldTransform().Scale.y * m_Model->GetFurthestLocalPoint().y,
										m_Owner->GetWorldTransform().Scale.z * m_Model->GetFurthestLocalPoint().z) ).Length() );


		if (renderer->GetCamera()->GetFrustum().IsSphereInFrustum(m_FrustumCollision))
		{
			for (uint32 i = 0; i < m_Model->GetMeshesSize(); i++)
			{
				m_Model->GetMesh(i)->GetMaterial().SetParamMatrix4D(String("u_view").GetStringID(), renderer->GetCamera()->GetView());
				m_Model->GetMesh(i)->GetMaterial().SetParamMatrix4D(String("u_projection").GetStringID(), renderer->GetCamera()->GetProjection());
				m_Model->GetMesh(i)->GetMaterial().SetParamVector3D(String("u_cameraPosition").GetStringID(), renderer->GetCamera()->GetPosition());
			}
			m_Model->SetTransformation(m_Owner->GetWorldTransformMatrix());
			if (m_Model != nullptr)
				m_Model->Draw();
		}

	}
}
