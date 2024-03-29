// Cu Nhat Hoang


#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Controller/BasePlayerController.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/UserInterface/HUD/MyHUD.h"
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
	ActiveAbilities();
}

void APlayerCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	if (!IsPlayerStateValid()) return;
	AbilitySystemComponent = Cast<UMyAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent());
	AbilitySystemComponent->BindCallBackToDependencies();
	AttributeSet = MyPlayerState->GetAttributeSet();
	if (HasAuthority() && AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(Cast<AActor>(MyPlayerState), this);
		InitAttributeValue();
	}
	if (IsPlayerControllerValid() && IsHudValid())
	{
		const FWidgetControllerParamsStruct WidgetControllerStruct(AbilitySystemComponent, AttributeSet, PlayerController, GetPlayerState<AMyPlayerState>());
		HUD->SetupWidget(WidgetControllerStruct);
	}
}

bool APlayerCharacter::IsHudValid()
{
	if (!HUD) HUD = PlayerController->GetHUD<AMyHUD>();
	return HUD != nullptr;
}

bool APlayerCharacter::IsPlayerControllerValid()
{
	if (!PlayerController) PlayerController = Cast<ABasePlayerController>(GetController());
	return PlayerController != nullptr;
}

bool APlayerCharacter::IsPlayerStateValid()
{
	if (!MyPlayerState) MyPlayerState = Cast<AMyPlayerState>(GetPlayerState());
	return MyPlayerState != nullptr;
}
