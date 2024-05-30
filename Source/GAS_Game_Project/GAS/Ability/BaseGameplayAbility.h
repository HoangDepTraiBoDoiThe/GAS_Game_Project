// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

class UMyAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag AbilityStartupTag;

	UMyAbilitySystemComponent* GetMyASC();

private:
	TObjectPtr<UMyAbilitySystemComponent> MyASC;
};
