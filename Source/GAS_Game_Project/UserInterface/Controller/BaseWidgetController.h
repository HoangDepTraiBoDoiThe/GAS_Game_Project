// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GAS_Game_Project/Character/Player/PlayerState/MyPlayerState.h"
#include "GAS_Game_Project/Data/AbilityUIInforDataAsset.h"
#include "BaseWidgetController.generated.h"

class UMyAbilitySystemComponent;
class UBaseAttributeSet;
class ABasePlayerController;
class AMyPlayerState;
class UAttributeSet;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOnParamToViewSignature, const int32, ValueToBroadCast);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityUIInfoToViewSignature, FAbilityUIInfoStruct, AbilityUIInfoStruct);

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

	UFUNCTION(BlueprintCallable)
	virtual void BroadCastInitialValue() {};
	UFUNCTION(BlueprintCallable)
	virtual void BroadCastToDependencies();
	
	UFUNCTION(BlueprintCallable)
	void SetupWidgetControllerParams(const FWidgetControllerParamsStruct& FWidgetControllerParamsStruct);

	UFUNCTION(BlueprintCallable)
	virtual void BroadCastCharacterExperience();
		
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAbilityUIInfoToViewSignature AbilityUIInfoToViewSignature;
	
protected:
	void BroadCastAbilityInfoToDependencies();
	void AfterAbilitiesAddedToPlayer(const UAbilitySystemComponent* ASC);

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
