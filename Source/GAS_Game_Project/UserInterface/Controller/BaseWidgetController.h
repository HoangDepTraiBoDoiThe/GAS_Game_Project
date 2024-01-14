// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "UObject/NoExportTypes.h"
#include "BaseWidgetController.generated.h"

class UBaseAttributeSet;
class ABasePlayerController;
class AMyPlayerState;
class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
USTRUCT()
struct FWidgetControllerStruct
{
	GENERATED_BODY()
	
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	TObjectPtr<ABasePlayerController> PlayerController;
	TObjectPtr<AMyPlayerState> PlayerState;
};

UCLASS()
class GAS_GAME_PROJECT_API UBaseWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseWidgetController();

	void SetupWidgetController(const FWidgetControllerStruct& NewWidgetControllerStruct);

protected:
	void GameplayEffectApplyToSelf(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	
	FWidgetControllerStruct WidgetControllerStruct;

private:
	
};
