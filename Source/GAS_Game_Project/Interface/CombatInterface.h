// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
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
	virtual FVector WeaponLocation() = 0;
};
