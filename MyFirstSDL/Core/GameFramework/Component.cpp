#include "Component.h"
#include "SDL_log.h"

Component::Component()
{
	m_Owner = nullptr;
	m_UpdateOrder = {};
}

Component::~Component()
{}

void Component::Update(float deltaTime)
{
}
