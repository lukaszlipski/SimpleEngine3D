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
		for (uint32 i = 0; i < m_Model->GetMeshesSize(); i++)
		{
		m_Model->GetMesh(i)->GetMaterial().SetParamMatrix4D(String("u_view").GetStringID(), renderer->GetCamera()->GetView());
		m_Model->GetMesh(i)->GetMaterial().SetParamMatrix4D(String("u_projection").GetStringID(), renderer->GetCamera()->GetProjection());
		}
		m_Model->SetTransformation(m_Owner->GetWorldTransformMatrix());
		if(m_Model != nullptr)
			m_Model->Draw();
	}
}
