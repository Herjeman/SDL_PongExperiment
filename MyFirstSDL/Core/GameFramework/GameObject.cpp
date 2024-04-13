#include "GameObject.h"
#include "SDL_Log.h"

GameObject::GameObject(Game* game)
{
	m_Game = game;
	m_State = EGameObjectState::EUninitialized;
}

GameObject::~GameObject()
{}

void GameObject::Update(float deltaTime)
{
}