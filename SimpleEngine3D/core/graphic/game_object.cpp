#include "game_object.h"
#include "components/component.h"

namespace SE3D
{

	GameObject::GameObject()
		: m_Parent(nullptr), m_DirtyFlag(false)
	{
		m_WorldTransformM = m_LocalTransform.GetMatrix();
	}

	void GameObject::Init()
	{
		UpdateWorldTransform();
		for (int32 i = 0; i < m_Components.Size(); i++)
			m_Components[i]->Init();

		for (int32 i = 0; i < m_Children.Size(); i++)
			m_Children[i]->Init();
	}

	void GameObject::Input(float DeltaTime)
	{
		UpdateWorldTransform();
		for (int32 i = 0; i < m_Components.Size(); i++)
			m_Components[i]->Input(DeltaTime);

		for (int32 i = 0; i < m_Children.Size(); i++)
			m_Children[i]->Input(DeltaTime);
	}

	void GameObject::Update(float DeltaTime)
	{
		UpdateWorldTransform();
		for (int32 i = 0; i < m_Components.Size(); i++)
			m_Components[i]->Update(DeltaTime);

		for (int32 i = 0; i < m_Children.Size(); i++)
			m_Children[i]->Update(DeltaTime);
	}

	void GameObject::Render()
	{
		UpdateWorldTransform();
		for (int32 i = 0; i < m_Components.Size(); i++)
			m_Components[i]->Render();

		for (int32 i = 0; i < m_Children.Size(); i++)
			m_Children[i]->Render();
	}

	void GameObject::AddChild(GameObject& go)
	{
		m_Children.Push(&go);
		go.m_Parent = this;
	}

	void GameObject::AddComponent(Component& component)
	{
		m_Components.Push(&component);
		component.SetOwner(*this);
	}

	void GameObject::SetPosition(const Vector3D& position)
	{
		if (position == m_LocalTransform.Position)
			return;
		m_DirtyFlag = true;
		m_LocalTransform.Position = position;
	}

	void GameObject::SetRotation(const Quaternion& rotation)
	{
		if (rotation == m_LocalTransform.Rotation)
			return;
		m_DirtyFlag = true;
		m_LocalTransform.Rotation = rotation;
	}

	void GameObject::SetScale(const Vector3D& scale)
	{
		if(scale == m_LocalTransform.Scale)
			return;
		m_DirtyFlag = true;
		m_LocalTransform.Scale = scale;
	}

	void GameObject::UpdateWorldTransform()
	{
		if (!m_DirtyFlag)
		{
			return;
		}

		for(int32 i =0;i<m_Children.Size();i++)
		{
			m_Children[i]->m_DirtyFlag = true;
		}

		if(!m_Parent)
		{
			m_WorldTransformM = m_LocalTransform.GetMatrix();
			m_DirtyFlag = false;
			return;
		}

		m_DirtyFlag = false;
		m_WorldTransformM = m_LocalTransform.GetMatrix() * m_Parent->m_WorldTransformM;

	}

}
