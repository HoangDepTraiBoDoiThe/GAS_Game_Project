// Cu Nhat Hoang


#include "MyBlueprintFunctionLibrary.h"
#include "GAS_Game_Project/GameRules/MyGameModeBase.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/Ability/BaseGameplayAbility.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS_Game_Project/UserInterface/HUD/MyHUD.h"
#include "Kismet/GameplayStatics.h"

UOverlayWidgetController* UMyBlueprintFunctionLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	const FWidgetControllerParamsStruct WidgetControllerParamsStruct = MakeWidgetControllerParamsStruct(WorldContextObject);
	AMyHUD* MyHUD = Cast<AMyHUD>(WidgetControllerParamsStruct.PlayerController->GetHUD());
	return MyHUD->GetOverlayWidgetController(WidgetControllerParamsStruct);
}

UAttributeMenuWidgetController* UMyBlueprintFunctionLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	const FWidgetControllerParamsStruct WidgetControllerParamsStruct = MakeWidgetControllerParamsStruct(WorldContextObject);
	AMyHUD* MyHUD = Cast<AMyHUD>(WidgetControllerParamsStruct.PlayerController->GetHUD());
	checkf(MyHUD, TEXT("Cant get MyHUD"))
	return MyHUD->GetAttributeMenuWidgetController(WidgetControllerParamsStruct);
}

void UMyBlueprintFunctionLibrary::InitAttributeValue(const ABaseGameCharacter* GameCharacter, const UObject* WorldContextObject)
{
	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!GameModeBase) return;
	
	GameCharacter->ApplyGameplayEffectToSelf(GameModeBase->CharacterClassInfoDataAsset->SecondaryDefaultAttribute);
	GameCharacter->ApplyGameplayEffectToSelf(GameModeBase->CharacterClassInfoDataAsset->VitalDefaultAttribute);
	for (TTuple<ECharacterClass, FCharacterClassDefaultMainInfosStruct>& CharacterDefaultClass : GameModeBase->CharacterClassInfoDataAsset->CharacterDefaultInfoMap)
	{
		if (GameCharacter->GetCharacterClass() == CharacterDefaultClass.Key)
			GameCharacter->ApplyGameplayEffectToSelf(CharacterDefaultClass.Value.PrimaryDefaultAttributes);
	}
}

void UMyBlueprintFunctionLibrary::AddAbilities(UAbilitySystemComponent* ASC, const UObject* WorldContextObject)
{
	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!GameModeBase) return;
	ABaseGameCharacter* GameCharacter = Cast<ABaseGameCharacter>(ASC->GetAvatarActor());
	for (const TSubclassOf<UGameplayAbility> AbilityClass : GameModeBase->CharacterClassInfoDataAsset->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, GameCharacter->GetCharacterLevel());
		ASC->GiveAbility(AbilitySpec);
	}
}

UCurveTable* UMyBlueprintFunctionLibrary::GetCoefficientCurveTable(const UObject* WorldContextObject)
{
	const AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	return GameModeBase->CharacterClassInfoDataAsset->CoefficientCurveTable.Get();
}

FWidgetControllerParamsStruct UMyBlueprintFunctionLibrary::MakeWidgetControllerParamsStruct(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	checkf(World, TEXT("Cant get World from WorldContextObject"))
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(World->GetFirstLocalPlayerFromController()->GetPlayerController(World));
	checkf(PlayerController, TEXT("Cant get ABasePlayerController"))
	AMyPlayerState* PlayerState = Cast<AMyPlayerState>(PlayerController->GetPlayerState<AMyPlayerState>());
	checkf(PlayerState, TEXT("Cant get PlayerState"))
	UMyAbilitySystemComponent* ASC = Cast<UMyAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent());
	UBaseAttributeSet* AttributeSet = Cast<UBaseAttributeSet>(PlayerState->GetAttributeSet());
	checkf(ASC, TEXT("Cant get ASC"))
	checkf(AttributeSet, TEXT("Cant get AttributeSet"))
	return FWidgetControllerParamsStruct(ASC, AttributeSet, PlayerController, PlayerState);
}
