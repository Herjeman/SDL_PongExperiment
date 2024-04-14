#include "Game.h"
#include <iostream>

#include <SDL.h>
#include <tuple>

#include "Core/Input/InputManager.h"

#include "Core/2DRendering/Renderer2D.h"
#include "Core/2DRendering/RenderComponent2D.h"
#include "Core/2DRendering/SpriteRenderComponent.h"
#include "Core/2DRendering/AnimatedSpriteComponent.h"
#include "Core/GameFramework/Actor.h"
#include "Core/AssetManagement/AssetManager.h"

#include "Game/Wall.h"
#include "Game/Paddle.h"
#include "Game/Ball.h"

Game::Game()
{
	m_Paddle = {};
	m_Ball = {};
}

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

	m_Renderer2D = new Renderer2D(this);
	m_AssetManager = new AssetManager();

	LoadData();
	
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
	m_Paddle->Init(50, 300, 16, 60); // not sure if init is the way to go... maybe just do definition in .h file for now. (Typesystem when?)
	m_Ball = AddGameObject<Ball>();
	m_Ball->GetComponent<RenderComponent2D>()->SetDrawOrder(18);

	Actor* image = AddGameObject<Actor>();
	image->SetTransform({ {300, 350},{2.f, 2.f}, 0.2});

	AnimatedSpriteComponent* comp = image->AddComponent<AnimatedSpriteComponent>();
	
	std::vector<std::string> animIDs;
	animIDs.push_back("Walk1");
	animIDs.push_back("Walk2");
	animIDs.push_back("Walk3");
	animIDs.push_back("Walk4");
	animIDs.push_back("Walk5");
	animIDs.push_back("Walk6");

	comp->SetTextureIDs(animIDs);
	comp->SetTexture(m_AssetManager->GetTexture("Walk1"));
	comp->SetDrawOrder(16);

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

	if (InputManager::Get().GetKeyDown(SDL_SCANCODE_ESCAPE))
	{
		m_IsRunning = false;
	}
}

void Game::Update()
{
	// Do time stuff
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 10));
	float deltaTime = (SDL_GetTicks64() - m_TicksCount) / 1000.f;
	m_TicksCount = SDL_GetTicks();

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
	m_Renderer2D->PreRender({ 50, 50, 230, 255 });
	m_Renderer2D->Render();
	m_Renderer2D->PostRender();
}

void Game::Clean()
{
	RemoveAllGameObjects();

	delete m_Renderer2D;
	delete m_AssetManager;
	SDL_DestroyWindow(m_Window);


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
		m_GameObjects[i]->Draw(renderer);
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
			return;
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

void Game::LoadData()
{
	std::vector<std::tuple<std::string, const char*>> textureLoadData;
	
	textureLoadData.push_back({ "Walk1", "Game/Assets/Character01.png"});
	textureLoadData.push_back({ "Walk2", "Game/Assets/Character02.png" });
	textureLoadData.push_back({ "Walk3", "Game/Assets/Character03.png" });
	textureLoadData.push_back({ "Walk4", "Game/Assets/Character04.png" });
	textureLoadData.push_back({ "Walk5", "Game/Assets/Character05.png" });
	textureLoadData.push_back({ "Walk6", "Game/Assets/Character06.png" });
	m_AssetManager->LoadTextures(textureLoadData, *m_Renderer2D->GetRenderer());
}

bool Game::IsRunning()
{
	return m_IsRunning;
}

FVector2 Game::GetWindowDimensions() const
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