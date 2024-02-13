// Cu Nhat Hoang


#include "MyAssetManager.h"

#include "GAS_Game_Project/GAS/GamplayTag/MyGameplayTags.h"

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	MyGameplayTags::Get().InitNativeGameplayTags();
}
