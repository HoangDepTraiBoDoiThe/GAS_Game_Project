// Cu Nhat Hoang


#include "SpellMenuWidgetController.h"

void USpellMenuWidgetController::BroadCastToDependencies()
{
	PlayerState->OnSpellPointChangeDelegate.AddLambda(
		[this] (const int32 SpellPoint)
		{
			OnSpellPointToViewDelegate.Broadcast(SpellPoint);			
		}
	);
}

void USpellMenuWidgetController::SpendSpellPoint(const int32 PointsToSpend)
{
	PlayerState->ChangeSpellPoint(-PointsToSpend);
}
