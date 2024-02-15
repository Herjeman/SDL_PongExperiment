#pragma once
#include "SDL.h"
#include <vector>

struct Vector2
{
	float X;
	float Y;
	Vector2() : X(0), Y(0) {}
	Vector2(float x, float y) : X(x), Y(y) {}

	Vector2 operator+ (const Vector2& vec)
	{
		Vector2 out;
		out.X = this->X + vec.X;
		out.Y = this->Y + vec.Y;
		return out;
	}

	Vector2 operator* (const float& factor)
	{
		Vector2 out;
		out.X = X * factor;
		out.Y = Y * factor;
		return out;
	}
};

struct Transform
{
	Vector2 Position;
	Vector2 Scale;
	float Rotation;
};

struct FColor
{
	int R = 0;
	int G = 0;
	int B = 0;
	int A = 0;
};

class Game
{
public:
	Game();
	~Game();

	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool Init(const char* title, int width, int height, bool fullscreen);
	void Run();

	bool IsRunning();
	Vector2 GetWindowDimensions();
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
	Uint64 m_TicksCount = 0;

	std::vector<class GameObject*> m_GameObjects;
	std::vector<class GameObject*> m_PendingGameObjects;
	std::vector<class GameObject*> m_GarbageGameObjects;

	class Paddle* m_Paddle;
	class Ball* m_Ball;

};

