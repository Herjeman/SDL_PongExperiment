#pragma once
#include "GameObject.h"
#include "Core/Utilities/Transform.h"
#include "Core/GameFramework/Component.h"
#include <vector>

class Actor : public GameObject
{
public:
	Actor(class Game* game);
	virtual ~Actor();

	virtual void Update(float deltaTime) override;
	void UpdateComponents(float deltaTime);

	template<typename T>
	T* AddComponent() {

		T* temp = new T(this);
		m_Components.push_back(temp);
		m_Components.back()->m_Owner = this;
		return temp;
	}

	void RemoveComponent(class Component* component);

	FTransform& GetTransform() { return m_Transform; }
	void SetTransform(FTransform newTransform) { m_Transform = newTransform; }

	FVector2 GetPosition() const { return m_Transform.Position; }
	void SetPosition(FVector2 position) { m_Transform.Position = position; }

	float GetRotation() const { return m_Transform.Rotation; }
	void SetRotation(float rotation) { m_Transform.Rotation = rotation; }

	FVector2 GetScale() const { return m_Transform.Scale; }
	void SetScale(FVector2 scale) { m_Transform.Scale = scale; }
	
	template<typename T>
	T* GetComponent();


protected:
	FTransform m_Transform;
private:
	std::vector<class Component*> m_Components;
};

template<class T>
inline T* Actor::GetComponent()
{
	for (Component* comp : m_Components)
	{
		T* out = dynamic_cast<T*>(comp);
		if (out)
		{
			return out;
		}
	}
	return nullptr;
}
