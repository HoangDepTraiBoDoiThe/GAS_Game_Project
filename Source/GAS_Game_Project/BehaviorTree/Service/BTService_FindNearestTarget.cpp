// Cu Nhat Hoang


#include "BTService_FindNearestTarget.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "GAS_Game_Project/Character/BaseGameCharacter.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	
	TArray<AActor*> Targets;
	ABaseGameCharacter* NearestTarget = nullptr;
	float DistanceToTarget = 5000;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Player", Targets);
	for (AActor* Target : Targets)
	{
		float Distance = AIOwner->GetPawn()->GetDistanceTo(Target);
		if (DistanceToTarget > Distance)
		{
			DistanceToTarget = Distance;
			NearestTarget = Cast<ABaseGameCharacter>(Target);
		}
	}
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetActor, NearestTarget);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToNearestTarget, DistanceToTarget);
}
