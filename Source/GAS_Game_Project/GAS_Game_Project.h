// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define ECC_PROJECTILE ECollisionChannel::ECC_GameTraceChannel1

UENUM(BlueprintType)
enum EDamageType : uint8
{
	EDT_Physical,
	EDT_Fire,
	EDT_Water,
	EDT_Wind,
	EDT_NONE
};
