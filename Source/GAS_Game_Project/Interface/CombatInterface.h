// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAS_GAME_PROJECT_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual float GetCharacterLevel() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector WeaponLocation();
	virtual AActor* GetWeapon() = 0;
	virtual void Die() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCurTarget(AActor* Actor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetCurTarget();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartMotionWarping(FVector TargetLocation);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IncreaseMinionMinionCount(int32 Val);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetMinionMinionCount();	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetMinionThreadHold();
};
