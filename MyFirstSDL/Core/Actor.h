#pragma once
#include "GameObject.h"
#include "Game.h" // needs because transform, move all structs to minimal.h or smth?
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
	Transform GetTransform() const { return m_Transform; }
	void SetTransform(Transform newTransform) { m_Transform = newTransform; }

protected:
	Transform m_Transform{};
private:
	std::vector<class Component*> m_Components;
};