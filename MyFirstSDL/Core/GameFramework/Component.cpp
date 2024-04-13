#include "Component.h"
#include "SDL_log.h"

Component::Component(Actor* owner, int updateOrder)
{
	m_Owner = owner;
	m_UpdateOrder = updateOrder;
}

Component::~Component()
{}

void Component::Update(float deltaTime)
{
}
