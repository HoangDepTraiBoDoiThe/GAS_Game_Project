// Cu Nhat Hoang


#include "BaseAnimInstance.h"

#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"

UBaseAnimInstance::UBaseAnimInstance()
{
	
}

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (TryGetPawnOwner()) MovementSpeed = GetCharacter()->GetVelocity().Size();
}

ACharacter* UBaseAnimInstance::GetCharacter()
{
	if (!Character) Character = Cast<ACharacter>(TryGetPawnOwner());
	return Character;
}

