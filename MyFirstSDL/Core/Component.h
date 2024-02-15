#pragma once
class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100); // Update priority makes more sense?
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void Draw(struct SDL_Renderer* renderer) { return; }

	// Getters and Setters
	int GetUpdateOrder() const { return m_UpdateOrder; }
	class Actor* GetOwner() const { return m_Owner; }

protected:
	class Actor* m_Owner = nullptr;
	int m_UpdateOrder = 0;
};

