// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfoDataAsset.generated.h"

/**
 * 
 */

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	ECC_Warrior,
	ECC_Ranger,
	ECC_Witch,
};

USTRUCT()
struct FCharacterClassDefaultMainInfosStruct
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere, Category=CharacterPrimary)
	TObjectPtr<UGameplayEffect> PrimaryDefaultAttributes;
};

UCLASS()
class GAS_GAME_PROJECT_API UCharacterClassInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE FCharacterClassDefaultMainInfosStruct GetCharacterClassDefaultMainInfosStruct(const ECharacterClass& CharacterClass) {return CharacterDefaultInfoMap.FindChecked(CharacterClass);}
	
	UPROPERTY(EditAnywhere, Category=CharacterPrimary)
	TMap<ECharacterClass, FCharacterClassDefaultMainInfosStruct> CharacterDefaultInfoMap;

	UPROPERTY(EditAnywhere, Category=CharacterCommon)
	TObjectPtr<UGameplayEffect> SecondaryDefaultAttribute;
	
	UPROPERTY(EditAnywhere, Category=CharacterCommon)
	TObjectPtr<UGameplayEffect> VitalDefaultAttribute;
};
