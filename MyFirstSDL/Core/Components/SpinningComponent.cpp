#include "SpinningComponent.h"
#include "Core/GameFramework/Actor.h"

void SpinningComponent::Update(float deltaTime)
{
	GetOwner()->SetRotation(GetOwner()->GetRotation() + deltaTime * Speed);
}
