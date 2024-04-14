#include "AnimatedSpriteComponent.h"
#include "Core/GameFramework/Actor.h"
#include "Game.h"
#include "Core/AssetManagement/AssetManager.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* owner) : SpriteRenderComponent(owner)
{}

void AnimatedSpriteComponent::Update(float deltaTime)
{
	m_CurrentFrameElapsedTime += deltaTime * m_AnimationSpeed;
	if (m_CurrentFrameElapsedTime >= m_TargetFrameTime && m_CurrentAnimation && m_CurrentAnimation->IsSet())
	{
		m_Texture = GetOwner()->GetGame()->GetAssetManager()->GetTexture(m_CurrentAnimation->GetNextID()); // hmmm...
		m_CurrentFrameElapsedTime = 0;
	}
}

void AnimatedSpriteComponent::SetTargetFPS(const int FPS)
{
	m_TargetFrameTime = 1.0f / (float)FPS;
}

AnimationData* AnimatedSpriteComponent::GetAnimationData(const std::string id)
{
	if (m_AnimationData.find(id) != m_AnimationData.end())
	{
		return &m_AnimationData[id];
	}
	return nullptr;
}

void AnimatedSpriteComponent::AddNewAnimationData(std::string AnimationID, std::vector<std::string> TextureIDs)
{
	if (m_AnimationData.find(AnimationID) != m_AnimationData.end())
	{
		return;
	}
	m_AnimationData[AnimationID] = AnimationData(TextureIDs);
}

void AnimatedSpriteComponent::SetAnimation(std::string animationID)
{
	if (AnimationData* animData = GetAnimationData(animationID))
	{
		m_CurrentAnimation = animData;
		SetTexture(GetOwner()->GetGame()->GetAssetManager()->GetTexture(m_CurrentAnimation->TextureIDs[0]));
	}
}

std::string AnimationData::GetNextID()
{
	AnimIndex++;
	if (AnimIndex >= TextureIDs.size())
	{
		AnimIndex -= TextureIDs.size();
	}
	return TextureIDs[AnimIndex];
}
