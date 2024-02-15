#include "GameObject.h"
#include "SDL_Log.h"

GameObject::GameObject(Game* game)
{
	m_Game = game;
	m_State = EGameObjectState::EUninitialized;
	SDL_Log("GameObject created");
}

GameObject::~GameObject()
{
	SDL_Log("GameObject destroyed");
}

void GameObject::Update(float deltaTime)
{
}