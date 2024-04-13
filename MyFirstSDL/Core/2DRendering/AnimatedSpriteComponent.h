#pragma once

#include <vector>
#include <string>
#include "Core/2DRendering/SpriteRenderComponent.h"

class AnimatedSpriteComponent : public SpriteRenderComponent
{
public:

	virtual void Update(float deltaTime) override;

	float GetTargetAnimationFrameTime() { return m_TargetFrameTime; }
	float SetTargetAnimationFrameTime(float time) { m_TargetFrameTime = time; }

private:

	std::vector<std::string> m_TextureIDs;
	float m_CurrentFrameElapsedTime;
	float m_TargetFrameTime;
};

