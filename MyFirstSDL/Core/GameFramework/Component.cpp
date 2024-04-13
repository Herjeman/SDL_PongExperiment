#include "Component.h"
#include "SDL_log.h"

Component::Component(Actor* owner, int updateOrder)
{
	m_Owner = owner;
	m_UpdateOrder = updateOrder;
	SDL_Log("Component created");
}

Component::~Component()
{
	SDL_Log("Component destroyed");
}

void Component::Update(float deltaTime)
{
}
