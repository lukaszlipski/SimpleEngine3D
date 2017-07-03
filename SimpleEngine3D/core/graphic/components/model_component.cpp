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
		Vector3D furthestPointFromMassCenter = m_Model->GetFurthestLocalPoint() - m_Model->GetMassCenter();
		m_FrustumCollision = Sphere(m_Owner->GetWorldTransform().Position,
			(Vector3D(m_Owner->GetWorldTransform().Scale.x * furthestPointFromMassCenter.x,
				m_Owner->GetWorldTransform().Scale.y * furthestPointFromMassCenter.y,
				m_Owner->GetWorldTransform().Scale.z * furthestPointFromMassCenter.z)).Length());

		renderer->AddObjectToRender(*this);

	}

	void ModelComponent::PutOnScreen(DeferredRenderer *renderer,Material *mat)
	{
		if (mat == 0)
		{
			for (uint32 i = 0; i < m_Model->GetMeshesSize(); i++)
			{
				m_Model->GetMesh(i)->GetMaterial().SetParamMatrix4D(String("u_view").GetStringID(), renderer->GetCamera()->GetView());
				m_Model->GetMesh(i)->GetMaterial().SetParamMatrix4D(String("u_projection").GetStringID(), renderer->GetCamera()->GetProjection());
				m_Model->GetMesh(i)->GetMaterial().SetParamVector3D(String("u_cameraPosition").GetStringID(), renderer->GetCamera()->GetPosition());
			}

		}

		m_Model->SetTransformation(m_Owner->GetWorldTransformMatrix());


		if (m_Model != nullptr)
			m_Model->Draw(mat);

	}

}
