#pragma once
#include "SDL.h"


class InputManager
{
public:
	InputManager(const InputManager& obj) = delete;
	InputManager& operator=(const InputManager&) = delete;

	static InputManager& Get();
	static void Update();
	bool GetKeyDown(const SDL_Scancode key);

private:
	InputManager();
	~InputManager(){}
	const Uint8* m_State;
	//static InputManager* m_InputManager;
};

