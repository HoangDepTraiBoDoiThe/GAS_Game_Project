// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearestTarget.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UBTService_FindNearestTarget : public UBTService_BlueprintBase
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActor;
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector DistanceToNearestTarget;
};
