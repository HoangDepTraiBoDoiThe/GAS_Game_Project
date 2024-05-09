// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfoDataAsset.generated.h"

/**
 * 
 */

class UBaseGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	ECC_Warrior,
	ECC_Ranger,
	ECC_Witch,
	ECC_None
};

USTRUCT()
struct FCharacterClassDefaultMainInfosStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category=CharacterPrimary)
	TSubclassOf<UGameplayEffect> PrimaryDefaultAttributes;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UBaseGameplayAbility>> ClassAbilities;
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
	TSubclassOf<UGameplayEffect> SecondaryDefaultAttribute;
	
	UPROPERTY(EditAnywhere, Category=CharacterCommon)
	TSubclassOf<UGameplayEffect> VitalDefaultAttribute;

	UPROPERTY(EditAnywhere, Category=CharacterCommon)
	TArray<TSubclassOf<UBaseGameplayAbility>> CommonAbilities;

	UPROPERTY(EditAnywhere, Category=CharacterCommon)
	TObjectPtr<UCurveTable> CoefficientCurveTable;
};
