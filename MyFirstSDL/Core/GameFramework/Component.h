#pragma once
class Component
{
public:
	Component(class Actor* owner);
	virtual ~Component();
	// To-Do: Add Init function
	virtual void Update(float deltaTime);

	// Getters and Setters
	int GetUpdateOrder() const { return m_UpdateOrder; }
	class Actor* GetOwner() const { return m_Owner; }

protected:
	class Actor* m_Owner = nullptr;
	int m_UpdateOrder = 0;
};

