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

	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(NewController);
	HUD = PlayerController->GetHUD<AMyHUD>();
	if (HUD)
	{
		FWidgetControllerParamsStruct WidgetControllerStruct(AbilitySystemComponent, AttributeSet, PlayerController, GetPlayerState<AMyPlayerState>());
		HUD->SetupWidget(WidgetControllerStruct);
	}
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
	AbilitySystemComponent = Cast<UMyAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent());
	AbilitySystemComponent->BindCallBackToDependencies();
	AttributeSet = MyPlayerState->GetAttributeSet();
	if (HasAuthority() && AbilitySystemComponent) AbilitySystemComponent->InitAbilityActorInfo(Cast<AActor>(MyPlayerState), this);
}
