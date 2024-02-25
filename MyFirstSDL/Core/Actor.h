#pragma once
#include "GameObject.h"
#include "Transform.h"
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
		return temp;
	}

	template<typename T, typename ... Args>
	T* AddComponent(Args ... args) {

		T* temp = new T(this, args...);
		m_Components.push_back(temp);
		return temp;
	}


	void RemoveComponent(class Component* component);

	// Getters and Setters
	FTransform GetTransform() const { return m_Transform; }
	void SetTransform(FTransform newTransform) { m_Transform = newTransform; }
	
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
