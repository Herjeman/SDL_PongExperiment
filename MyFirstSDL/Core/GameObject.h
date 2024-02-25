#pragma once

// Not sure what to do with this class currently, I imagine it should be related to memory management and stuff

class GameObject
{
public:
	enum EGameObjectState
	{
		EUninitialized,
		EActive,
		EInactive,
		EPendingRemoval
	};

	GameObject(class Game* game);
	virtual ~GameObject();

	// Functions and stuff, maybe add an Init and OnInit?
	virtual void Update(float deltaTime);
	virtual void Draw(struct SDL_Renderer* renderer) { return; };

	// Getters and Setters
	EGameObjectState GetState() { return m_State; }
	void SetState(EGameObjectState newState) { m_State = newState; }

	class Game* GetGame() { return m_Game; }

private:
	EGameObjectState m_State;
	class Game* m_Game = nullptr;
};

