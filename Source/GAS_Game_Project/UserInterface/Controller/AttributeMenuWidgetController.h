// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FAttributeInfoStruct;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayAttributeMenuSignature, const FAttributeInfoStruct&, AttributeInfoStruct);


UCLASS()
class GAS_GAME_PROJECT_API UAttributeMenuWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	void BroadCastAttributeValue(const FGameplayTag& Tag, const FGameplayAttribute& GameplayAttribute) const;
	virtual void BroadCastInitialValue() override;
	virtual void BroadCastToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnGameplayAttributeMenuSignature OnGameplayAttributeMenu;

	UFUNCTION()
	FORCEINLINE FOnGameplayAttributeMenuSignature& GetOnGameplayAttributeMenu () {return OnGameplayAttributeMenu;}
	
protected:
	
};
