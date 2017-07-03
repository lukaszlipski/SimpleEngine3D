#pragma once
#include "../game_object.h"

namespace SE3D
{
	class Component
	{
	protected:
		GameObject *m_Owner;

	public:
		inline virtual void SetOwner(GameObject& go)
		{
			m_Owner = &go;
		}

		inline virtual GameObject *GetOwner() { return m_Owner; }

		virtual ~Component() = default;
		virtual void Init() = 0;
		virtual void Input(float DeltaTime) = 0;
		virtual void Update(float DeltaTime) = 0;
		virtual void Render(DeferredRenderer *renderer) = 0;

	};
}
