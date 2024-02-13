// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"
#include "GAS_Game_Project/Character/Player/Controller/BasePlayerController.h"
#include "OverlayWidgetController.generated.h"

class UBaseUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageGameplayTag = FGameplayTag();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBaseUserWidget> MessageWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MessageTexture2D;
};

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayAttributeInitValuesSignature, const float, NewValue, FGameplayAttribute, Attribute);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayEffectWidgetMessageStructToViewSignature, const FUIWidgetRow&, UIWidgetRow);

UCLASS()
class GAS_GAME_PROJECT_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()


public:
	virtual void BroadCastInitialValue() override;
	virtual void BroadCastToDependencies() override;
	template <class T>
	T* GetUIWidgetRowData(const FGameplayTag& MessageTag);

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayAttributeInitValuesSignature OnAttributeInitialValuesSignature;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayEffectWidgetMessageStructToViewSignature OnGameplayEffectWidgetMessageStructToViewDelegate;

protected:

	
};

template <class T>
T* UOverlayWidgetController::GetUIWidgetRowData(const FGameplayTag& MessageTag)
{
	return PlayerController->GetPawn<APlayerCharacter>()->GetUIWidgetDataTable()->FindRow<T>(MessageTag.GetTagName(), FString(""));
}
