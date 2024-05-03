// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "MyGameplayEffectTypes.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FMyGameplayEffectContext : public FGameplayEffectContext
{
 GENERATED_BODY()

public:
 FORCEINLINE bool IsCriticalHit() const
 {
  return bIsCriticalHit;
 }

 FORCEINLINE void SetIsCriticalHit(bool bCriticalHit)
 {
  this->bIsCriticalHit = bCriticalHit;
 }

 FORCEINLINE bool IsHitBlocked() const
 {
  return bIsHitBlocked;
 }

 FORCEINLINE void SetIsHitBlocked(bool bHitBlocked)
 {
  this->bIsHitBlocked = bHitBlocked;
 }

 virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
 virtual UScriptStruct* GetScriptStruct() const override;

protected:
 UPROPERTY()
 bool bIsCriticalHit{false};
 UPROPERTY()
 bool bIsHitBlocked{false};
 
};

template<>
struct TStructOpsTypeTraits< FMyGameplayEffectContext > : public TStructOpsTypeTraitsBase2< FMyGameplayEffectContext >
{
 enum
 {
  WithNetSerializer = true,
  WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
 };
};