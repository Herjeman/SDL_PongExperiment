#pragma once
#include <vector>
#include <map>


class Game
{
public:
	Game();
	~Game();

	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool Init(const char* title, int width, int height, bool fullscreen);
	void Run();

	bool IsRunning();

	struct SDL_Window* GetWindow() const { return m_Window; }
	struct FVector2 GetWindowDimensions() const;
	class Renderer2D* GetRenderer() const { return m_Renderer2D; }
	class AssetManager* GetAssetManager() const { return m_AssetManager; }

	class Paddle* GetPaddle()const { return m_Paddle; }

	int BorderThickness = 16;

private:
	void ProcessInput();
	void Update();
	void GenerateOutput();
	void Render();
	void Clean();

	template<class T>
	T* AddGameObject() 
	{
		T* temp = new T(this);
		m_GameObjects.push_back(temp);
		return temp;
	}

	void UpdateGameObjects(float deltaTime);
	void DrawGameObjects(struct SDL_Renderer* renderer);
	void RemoveGameObject(class GameObject* object);
	void RemoveAllGameObjects();
	void ClearGarbageGameObjects();

	void LoadData();

	void CreateWalls(int thickness);

private:
	bool m_IsRunning = false;
	struct SDL_Window* m_Window = nullptr;
	int m_TicksCount = 0;

	class Renderer2D* m_Renderer2D = nullptr;
	class AssetManager* m_AssetManager = nullptr;

	std::vector<class GameObject*> m_GameObjects;
	std::vector<class GameObject*> m_PendingGameObjects;
	std::vector<class GameObject*> m_GarbageGameObjects;

	class Paddle* m_Paddle;
	class Ball* m_Ball;
	class AnimatedSpriteComponent* m_Sprite;
};

