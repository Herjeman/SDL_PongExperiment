#include "AnimatedSpriteComponent.h"
#include "Core/GameFramework/Actor.h"
#include "Game.h"
#include "Core/AssetManagement/AssetManager.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* owner) : SpriteRenderComponent(owner)
{}

void AnimatedSpriteComponent::Update(float deltaTime)
{
	m_CurrentFrameElapsedTime += deltaTime * m_AnimationSpeed;
	if (m_CurrentFrameElapsedTime >= m_TargetFrameTime && m_TextureIDs.size() > 0)
	{
		m_Texture = GetOwner()->GetGame()->GetAssetManager()->GetTexture(GetNextTextureId()); // hmmm...
		m_CurrentFrameElapsedTime = 0;
	}
}

void AnimatedSpriteComponent::SetTargetFPS(const int FPS)
{
	m_TargetFrameTime = 1.0f / (float)FPS;
}

std::string AnimatedSpriteComponent::GetNextTextureId()
{
	m_TextureIndex++;
	if (m_TextureIndex >= m_TextureIDs.size())
	{
		m_TextureIndex -= m_TextureIDs.size();
	}
	return m_TextureIDs[m_TextureIndex];
}
