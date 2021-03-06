#pragma once
#include "../containers/dynamic_array.h"
#include "../math/transform.h"

namespace SE3D
{
	class DeferredRenderer;
	class Component;

	class GameObject
	{
	private:
		GameObject *m_Parent;
		DynamicArray<GameObject*> m_Children;
		DynamicArray<Component*> m_Components;
		Transform m_LocalTransform;
		Transform m_WorldTransform;
		Matrix4D m_WorldTransformM;
		bool m_DirtyFlag;
			
	public:
		GameObject();

		void Init();
		void Input(float DeltaTime);
		void Update(float DeltaTime);
		void Render(DeferredRenderer *renderer);

		void AddChild(GameObject& go);
		void AddComponent(Component& component);

		inline Vector3D GetPosition() const { return m_LocalTransform.Position; };
		void SetPosition(const Vector3D& position);
		inline Quaternion GetRotation() const { return m_LocalTransform.Rotation; };
		void SetRotation(const Quaternion& rotation);
		inline Vector3D GetScale() const { return m_LocalTransform.Scale; };
		void SetScale(const Vector3D& scale);

		inline Transform GetLocalTransform() const { return m_LocalTransform; }
		inline Transform GetWorldTransform() const { return m_WorldTransform; }
		inline Matrix4D GetWorldTransformMatrix() const { return m_WorldTransformM; }

	private:
		void UpdateWorldTransform();

	};
}
