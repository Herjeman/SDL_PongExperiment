#include "Game.h"
//#include "SDL.h"
#include "iostream"
#include "Actor.h"
#include "Component.h"
#include "GameObject.h"
#include "RectRenderComponent.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"

Game::Game()
{}

Game::~Game()
{}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (!(SDL_Init(SDL_INIT_VIDEO) == 0))
	{	
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	std::cout << "SDL initialized... \n";

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	m_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

	if (!m_Window)
	{
		std::cout << "Window creation failed" << std::endl;
		return false;
	}
	std::cout << "Window created... \n";

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_Renderer)
	{
		std::cout << "Renderer creation failed " << std::endl;
		return false;
	}
	std::cout << "Renderer initialized... " << std::endl;
	
	return true;
}

bool Game::Init(const char* title, int width, int height, bool fullscreen)
{
	return Init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen);
}

void Game::Run()
{	
	CreateWalls(BorderThickness);

	m_Paddle = AddGameObject<Paddle>();
	m_Paddle->Init(50, 300, 16, 60); // not sure if init is the way to go... maybe just do definition in .h file for now

	m_Ball = AddGameObject<Ball>();

	m_IsRunning = true;
	while (m_IsRunning)
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}

	Clean();
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_IsRunning = false;
			break;
		default:
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		m_IsRunning = false;
	}
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		m_Paddle->AddUpInput();
	}
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		m_Paddle->AddDownInput();
	}
}

void Game::Update()
{
	// Do time stuff
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 10));
	float deltaTime = (SDL_GetTicks64() - m_TicksCount) / 1000.f;
	m_TicksCount = SDL_GetTicks64();

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	UpdateGameObjects(deltaTime);
}

void Game::GenerateOutput()
{
	Render();
}

void Game::Render()
{
	// Setup
	SDL_SetRenderDrawColor(m_Renderer, 50, 50, 230, 255);
	SDL_RenderClear(m_Renderer);

	// Draw Gameobjects
	DrawGameObjects(m_Renderer);

	// Finish
	SDL_RenderPresent(m_Renderer);
}

void Game::Clean()
{
	RemoveAllGameObjects();

	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);

	std::cout << "Game cleaned" << std::endl;
}


void Game::UpdateGameObjects(float deltaTime)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Update(deltaTime);
	}
}

void Game::DrawGameObjects(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Draw(m_Renderer);
	}
}

void Game::RemoveGameObject(GameObject* object)
{
	if (!object)
	{
		return;
	}
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i] == object)
		{
			m_GameObjects.erase(m_GameObjects.begin() + i);
			delete object;
		}
	}
}

void Game::RemoveAllGameObjects()
{
	for (GameObject* object : m_GameObjects)
	{
		delete object;
	}
	m_GameObjects.clear();

	for (GameObject* object : m_PendingGameObjects)
	{
		delete object;
	}
	m_PendingGameObjects.clear();

	ClearGarbageGameObjects();
	SDL_Log("Cleared all GameObjects");
}

void Game::ClearGarbageGameObjects()
{
	for (GameObject* object : m_GarbageGameObjects)
	{
		delete object;
	}
	m_GarbageGameObjects.clear();
}

bool Game::IsRunning()
{
	return m_IsRunning;
}

Vector2 Game::GetWindowDimensions()
{
	int x, y;
	SDL_GetWindowSize(m_Window, &x, &y);
	return {(float)x, (float)y};
}

void Game::CreateWalls(int thickness)
{
	int width;
	int height;
	SDL_GetWindowSize(m_Window, &width, &height);

	Wall* wall = AddGameObject<Wall>();
	wall->Init(width * 0.5f, thickness * 0.5f, width, thickness);

	wall = AddGameObject<Wall>();
	wall->Init(width * 0.5f, height - thickness * 0.5f, width, thickness);

	wall = AddGameObject<Wall>();
	wall->Init(thickness * 0.5f, height * 0.5f, thickness, height);

	wall = AddGameObject<Wall>();
	wall->Init(width - thickness * 0.5f, height * 0.5f, thickness, height);
}