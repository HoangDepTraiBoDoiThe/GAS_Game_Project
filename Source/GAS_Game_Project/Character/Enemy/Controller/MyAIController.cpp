// Cu Nhat Hoang


#include "MyAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Black board");
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior tree component");
}
