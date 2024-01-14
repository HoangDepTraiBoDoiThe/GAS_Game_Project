// Cu Nhat Hoang


#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "PlayerState/MyPlayerState.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(GetPlayerState());
	if (!MyPlayerState) return;
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();
	if (HasAuthority() && AbilitySystemComponent) AbilitySystemComponent->InitAbilityActorInfo(Cast<AActor>(MyPlayerState), this);
}
