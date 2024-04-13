#include "InputManager.h"


InputManager::InputManager()
{
	m_State = SDL_GetKeyboardState(nullptr);
}

InputManager& InputManager::Get()
{
	static InputManager inputManager;
	return inputManager;
}

void InputManager::Update()
{
	SDL_PumpEvents();
}

bool InputManager::GetKeyDown(const SDL_Scancode key)
{
	return m_State[key];
}