#include "model_component.h"

namespace SE3D
{

	ModelComponent::ModelComponent(Model& model)
	{
		m_Model = &model;
	}

	void ModelComponent::Init() {}

	void ModelComponent::Update(float DeltaTime) {}

	void ModelComponent::Render()
	{
		m_Model->SetTransformation(m_Owner->GetWorldTransformMatrix());
		if(m_Model != nullptr)
			m_Model->Draw();
	}
}
