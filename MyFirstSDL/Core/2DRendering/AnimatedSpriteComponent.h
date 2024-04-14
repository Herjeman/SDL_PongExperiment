#pragma once

#include <vector>
#include <string>
#include "Core/2DRendering/SpriteRenderComponent.h"

class AnimatedSpriteComponent : public SpriteRenderComponent
{
public:

	AnimatedSpriteComponent(class Actor* owner);
	~AnimatedSpriteComponent(){}


	virtual void Update(float deltaTime) override;

	float GetTargetAnimationFrameTime() const { return m_TargetFrameTime; }
	void SetTargetAnimationFrameTime(const float time) { m_TargetFrameTime = time; }
	void SetTargetFPS(const int FPS);
	void SetAnimationSpeed(const float speed) { m_AnimationSpeed = speed; }
	float GetAnimationSpeed() const { return m_AnimationSpeed; }
	std::vector<std::string>& GetTextureIDs() { return m_TextureIDs; };
	void SetTextureIDs(std::vector<std::string> IDs) { m_TextureIDs = IDs; }

private:

	std::string GetNextTextureId();
	std::vector<std::string> m_TextureIDs;
	float m_CurrentFrameElapsedTime = 0;
	float m_TargetFrameTime = 0.2;
	float m_AnimationSpeed = 1;
	int m_TextureIndex = 0;
};

