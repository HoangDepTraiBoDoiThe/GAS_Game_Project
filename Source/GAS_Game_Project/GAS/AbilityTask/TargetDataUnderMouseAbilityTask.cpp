// Cu Nhat Hoang


#include "TargetDataUnderMouseAbilityTask.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouseAbilityTask* UTargetDataUnderMouseAbilityTask::TargetDataUnderMouse(
	UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouseAbilityTask* Obj = NewAbilityTask<UTargetDataUnderMouseAbilityTask>(
		OwningAbility, FName("Target Data Under Mouse Task"));
	return Obj;
}

void UTargetDataUnderMouseAbilityTask::Activate()
{
	if (Ability->GetAvatarActorFromActorInfo()->GetInstigatorController()->IsLocalController())
	{
		SetReplicateMouseTargetData();
	}
	else
	{
		AbilitySystemComponent->AbilityTargetDataSetDelegate(Ability->GetCurrentAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UTargetDataUnderMouseAbilityTask::OnTargetDataReceivedCallback);
		if (!AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(
			Ability->GetCurrentAbilitySpecHandle(), GetActivationPredictionKey()))
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouseAbilityTask::SetReplicateMouseTargetData() const
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	FGameplayAbilityTargetData_SingleTargetHit* Data_SingleTargetHit = new FGameplayAbilityTargetData_SingleTargetHit();
	Data_SingleTargetHit->HitResult = GetHitResult();
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data_SingleTargetHit);
	AbilitySystemComponent->ServerSetReplicatedTargetData(Ability->GetCurrentAbilitySpecHandle(),
	                                                      GetActivationPredictionKey(), DataHandle, FGameplayTag(),
	                                                      AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates()) ValidData.Broadcast(DataHandle);
}

FHitResult UTargetDataUnderMouseAbilityTask::GetHitResult() const
{
	const APlayerController* PlayerController = Cast<APlayerController>(Ability->GetAvatarActorFromActorInfo()->GetInstigatorController());
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	return HitResult;
}

void UTargetDataUnderMouseAbilityTask::OnTargetDataReceivedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag) const
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(Ability->GetCurrentAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates()) ValidData.Broadcast(DataHandle);
}
