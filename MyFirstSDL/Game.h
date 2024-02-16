#pragma once
#include <vector>


class Game
{
public:
	Game();
	~Game();

	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool Init(const char* title, int width, int height, bool fullscreen);
	void Run();

	bool IsRunning();
	struct FVector2 GetWindowDimensions();
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

	void CreateWalls(int thickness);

private:
	bool m_IsRunning = false;
	struct SDL_Window* m_Window = nullptr;
	struct SDL_Renderer* m_Renderer = nullptr;
	int m_TicksCount = 0;

	class std::vector<class GameObject*> m_GameObjects;
	class std::vector<class GameObject*> m_PendingGameObjects;
	class std::vector<class GameObject*> m_GarbageGameObjects;

	class Paddle* m_Paddle;
	class Ball* m_Ball;

};

