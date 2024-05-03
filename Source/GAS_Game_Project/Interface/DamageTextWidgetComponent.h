// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UDamageTextWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetDamageText(float DamgeTextValue);

	// Crit, blocked, etc
	UFUNCTION(BlueprintImplementableEvent)
	void SetDamageStatus(bool bCritHit, bool bBlockedHit);
	
protected:
	
};
