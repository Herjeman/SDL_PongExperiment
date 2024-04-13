#include "Actor.h"
#include "Component.h"
#include "SDL_log.h"

Actor::Actor(Game* game) : GameObject(game)
{
	SDL_Log("Actor GameObject created");
}

Actor::~Actor()
{
	for (Component* comp : m_Components)
	{
		delete comp;
	}
	m_Components.clear();
	SDL_Log("Actor GameObject destroyed");
}

void Actor::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	UpdateComponents(deltaTime);
}

void Actor::UpdateComponents(float deltaTime)
{
	for (Component* component : m_Components)
	{
		component->Update(deltaTime);
	}
}

void Actor::RemoveComponent(Component* component) // Destroy components here? Make this return false if no such component?
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		if (m_Components[i] == component)
		{
			m_Components.erase(m_Components.begin() + i);
			return;
		}
	}
	SDL_Log("Call to RemoveComponent found no Component to Remove!");
}
