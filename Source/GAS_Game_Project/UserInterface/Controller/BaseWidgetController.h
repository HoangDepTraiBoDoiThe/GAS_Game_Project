// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GAS_Game_Project/Character/Player/PlayerState/MyPlayerState.h"
#include "UObject/NoExportTypes.h"
#include "BaseWidgetController.generated.h"

class UMyAbilitySystemComponent;
class UBaseAttributeSet;
class ABasePlayerController;
class AMyPlayerState;
class UAttributeSet;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FWidgetControllerParamsStruct
{
	GENERATED_BODY()

	FWidgetControllerParamsStruct () {}
	FWidgetControllerParamsStruct (UMyAbilitySystemComponent* ASC, UBaseAttributeSet* AS, ABasePlayerController* PC, AMyPlayerState* PS)
		: PlayerController(PC), AbilitySystemComponent(ASC), AttributeSet(AS), PlayerState(PS) {}

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMyAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABasePlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMyPlayerState> PlayerState;
};

UCLASS(Blueprintable, BlueprintType)
class GAS_GAME_PROJECT_API UBaseWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseWidgetController();

	virtual void BroadCastInitialValue() {};
	virtual void BroadCastToDependencies() {};
	UFUNCTION(BlueprintCallable)
	void SetupWidgetControllerParams(const FWidgetControllerParamsStruct& FWidgetControllerParamsStruct);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMyAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABasePlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMyPlayerState> PlayerState;
	
private:
	
};
