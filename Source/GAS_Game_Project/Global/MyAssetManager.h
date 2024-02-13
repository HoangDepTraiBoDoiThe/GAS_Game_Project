// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	
protected:
	virtual void StartInitialLoading() override;
};
