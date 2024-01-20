// Cu Nhat Hoang


#include "BaseGameCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ABaseGameCharacter::ABaseGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ACharacter::GetMovementComponent()->bConstrainToPlane = true;
	ACharacter::GetMovementComponent()->bSnapToPlaneAtStart = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ABaseGameCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ABaseGameCharacter::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

