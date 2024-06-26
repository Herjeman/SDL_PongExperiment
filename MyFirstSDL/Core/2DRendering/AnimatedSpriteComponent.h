#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include "Core/2DRendering/SpriteRenderComponent.h"

struct FAnimationData
{
	FAnimationData(){}
	FAnimationData(std::vector<std::string> textureIDs) 
	{
		TextureIDs = textureIDs;
	}

	std::vector<std::string> TextureIDs;
	int AnimIndex = 0;

	bool IsSet()const { return TextureIDs.size() != 0; }

	std::string GetNextID();
};

class AnimatedSpriteComponent : public SpriteRenderComponent
{
public:
	virtual void Update(float deltaTime) override;

	float GetTargetAnimationFrameTime() const { return m_TargetFrameTime; }
	void SetTargetAnimationFrameTime(const float time) { m_TargetFrameTime = time; }
	void SetTargetFPS(const int FPS);
	void SetAnimationSpeed(const float speed) { m_AnimationSpeed = speed; }
	float GetAnimationSpeed() const { return m_AnimationSpeed; }
	FAnimationData* GetAnimationData(const std::string id);
	void AddNewAnimationData(std::string animationID, std::vector<std::string> textureIDs);
	void SetAnimation(std::string animationID);

private:
	FAnimationData* m_CurrentAnimation = nullptr;
	std::unordered_map<std::string, FAnimationData> m_AnimationData;
	float m_CurrentFrameElapsedTime = 0;
	float m_TargetFrameTime = 0.416;
	float m_AnimationSpeed = 1;
	int m_TextureIndex = 0;
};

