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

		virtual ~Component() = default;
		virtual void Init() = 0;
		virtual void Update(float DeltaTime) = 0;
		virtual void Render() = 0;
	};
}
