// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayAttributevalueChangeToControllerSignature, const FOnAttributeChangeData&)

UCLASS()
class GAS_GAME_PROJECT_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	void InitOwnerAndAvatarActor(AActor* OwnerActor, AActor* AvatarActor);
	void BindCallBackToDependencies();

	FGameplayAttributevalueChangeToControllerSignature OnNewAttributeValueChangeToControllerDelegate;

};
