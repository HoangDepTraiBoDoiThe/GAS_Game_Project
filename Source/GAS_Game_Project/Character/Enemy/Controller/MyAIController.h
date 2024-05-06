// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComponent() {return BehaviorTreeComponent;}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

private:
};
