// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAttributeInfoStruct
{
	GENERATED_BODY()

	FAttributeInfoStruct() {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttributeName = FName("Default");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue {0};
};
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE TArray<FAttributeInfoStruct> GetAttributeInfos () {return AttributeInfos;}
	FAttributeInfoStruct FindAttributeInfo (const FGameplayTag& GameplayTag);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAttributeInfoStruct> AttributeInfos;

private:
	
};
