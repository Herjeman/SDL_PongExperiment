#pragma once

class Component
{
friend class Actor;
public:
	Component();
	virtual ~Component();
	virtual void Update(float deltaTime);
	virtual void Initialize(){}

	// Getters and Setters
	int GetUpdateOrder() const { return m_UpdateOrder; }
	class Actor* GetOwner() const { return m_Owner; }

protected:
	class Actor* m_Owner = nullptr;
	int m_UpdateOrder = 0;
};

