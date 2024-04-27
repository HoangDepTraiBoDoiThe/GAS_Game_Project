// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GAS_Game_Project/UserInterface/Controller/AttributeMenuWidgetController.h"
#include "GAS_Game_Project/UserInterface/Controller/OverlayWidgetController.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */

UCLASS()
class GAS_GAME_PROJECT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	UFUNCTION(meta=(WorldContext = "WorldContextObject"))
	static void InitAttributeValue(const ABaseGameCharacter* GameCharacter, const UObject* WorldContextObject);
	static void AddAbilities(UAbilitySystemComponent* ASC, const UObject* WorldContextObject);
	
protected:
	static FWidgetControllerParamsStruct MakeWidgetControllerParamsStruct (const UObject* WorldContextObject);
	
private:
	
};
