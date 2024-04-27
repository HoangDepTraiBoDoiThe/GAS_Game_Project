// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GAS_Game_Project/Data/CharacterClassInfoDataAsset.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */



UCLASS()
class GAS_GAME_PROJECT_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UCharacterClassInfoDataAsset* CharacterClassInfoDataAsset;
	
};
