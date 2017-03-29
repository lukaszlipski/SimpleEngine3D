#pragma once
#include "component.h"
#include "../model.h"

namespace SE3D
{
	class ModelComponent : public Component
	{
	private:
		Model *m_Model;

	public:
		ModelComponent(Model& model);
		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer *renderer) override;

	};
}
