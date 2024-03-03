// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

class UAttributeInfo;
class UBaseAttributeSet;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API AMyPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UBaseAttributeSet* GetAttributeSet() const {return AttributeSet;}

	FORCEINLINE UAttributeInfo* GetAttributeInfo () const {return AttributeInfo;}
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	
	UPROPERTY(EditAnywhere)
	UAttributeInfo* AttributeInfo;
};
