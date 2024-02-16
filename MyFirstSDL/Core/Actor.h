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
	void Draw(struct SDL_Renderer* renderer) override;

	template<typename T>
	T* AddComponent() {

		T* temp = new T(this);
		m_Components.push_back(temp);
		return temp;
	}
	void RemoveComponent(class Component* component);

	// Getters and Setters
	FTransform GetTransform() const { return m_Transform; }
	void SetTransform(FTransform newTransform) { m_Transform = newTransform; }

protected:
	FTransform m_Transform;
private:
	std::vector<class Component*> m_Components;
};