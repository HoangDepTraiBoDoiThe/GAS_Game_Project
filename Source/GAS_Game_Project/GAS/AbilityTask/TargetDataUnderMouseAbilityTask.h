// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouseAbilityTask.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FValidData, FGameplayAbilityTargetDataHandle, DataHandle);
UCLASS()
class GAS_GAME_PROJECT_API UTargetDataUnderMouseAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="TRUE"), DisplayName="TargetDataUnderMouse")
	static UTargetDataUnderMouseAbilityTask* TargetDataUnderMouse(UGameplayAbility* OwningAbility);

private:
	virtual void Activate() override;
	void SetReplicateMouseTargetData() const;
	void OnTargetDataReceivedCallback(const FGameplayAbilityTargetDataHandle&, FGameplayTag) const;
	FHitResult GetHitResult() const;

	UPROPERTY(BlueprintAssignable)
	FValidData ValidData;
};
