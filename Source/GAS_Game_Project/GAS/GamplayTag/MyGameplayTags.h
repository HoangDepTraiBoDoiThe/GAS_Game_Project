// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GAS_GAME_PROJECT_API MyGameplayTags
{
public:
 static const MyGameplayTags& Get() {return GameplayTags;}

protected:

private:
 static MyGameplayTags GameplayTags;
 
}
;
