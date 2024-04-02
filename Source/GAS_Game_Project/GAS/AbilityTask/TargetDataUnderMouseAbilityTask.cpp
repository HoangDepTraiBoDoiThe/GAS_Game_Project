// Cu Nhat Hoang


#include "TargetDataUnderMouseAbilityTask.h"

UTargetDataUnderMouseAbilityTask* UTargetDataUnderMouseAbilityTask::TargetDataUnderMouse(
	UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouseAbilityTask* Obj = NewAbilityTask<UTargetDataUnderMouseAbilityTask>(
		OwningAbility, FName("Target Data Under Mouse Task"));
	return Obj;
}

void UTargetDataUnderMouseAbilityTask::Activate()
{
	const APlayerController* PlayerController = Cast<APlayerController>(
		Ability->GetAvatarActorFromActorInfo()->GetInstigatorController());
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	ValidData.Broadcast(HitResult.ImpactPoint);
}
