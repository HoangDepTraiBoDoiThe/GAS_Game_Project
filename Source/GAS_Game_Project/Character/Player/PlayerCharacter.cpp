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
	AbilitySystemComponent->AddAbilities(StartupAbilities, MyGameplayTags::Get().Ability_Availability_Equipped);
	AbilitySystemComponent->AddEventReceiver(EventReceiver, GetCharacterLevel());
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
	AbilitySystemComponent->InitAbilityActorInfo(Cast<AActor>(MyPlayerState), this);
	if (HasAuthority() && AbilitySystemComponent)
	{
		InitAttributeValue();
	}
	if (IsPlayerControllerValid() && IsHudValid())
	{
		const FWidgetControllerParamsStruct WidgetControllerStruct(AbilitySystemComponent, AttributeSet, PlayerController, GetPlayerState<AMyPlayerState>());
		HUD->SetupWidget(WidgetControllerStruct);
	}
}

int32 APlayerCharacter::GetCharacterLevel() const
{
	check(GetPlayerState())
	const int32 Level = Cast<AMyPlayerState>(GetPlayerState())->GetCharacterLevel();
	return Level;
}

int32 APlayerCharacter::GetCharacterXP()
{
	return GetMyPlayerState()->GetCharacterXP();
}

int32 APlayerCharacter::GetAttributePoint()
{
	return GetMyPlayerState()->GetAbilityPoint();
}

void APlayerCharacter::Die()
{
	
	Super::Die();
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

AMyPlayerState* APlayerCharacter::GetMyPlayerState()
{
	if (!MyPlayerState) MyPlayerState = Cast<AMyPlayerState>(GetPlayerState());
	return MyPlayerState;
}
