#include "Component.h"
#include "SDL_log.h"

Component::Component(Actor* owner)
{
	m_Owner = owner;
	m_UpdateOrder = {};
}

Component::~Component()
{}

void Component::Update(float deltaTime)
{
}
