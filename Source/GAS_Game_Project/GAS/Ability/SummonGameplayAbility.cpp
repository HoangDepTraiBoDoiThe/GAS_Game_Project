// Cu Nhat Hoang


#include "SummonGameplayAbility.h"

#include "GAS_Game_Project/Interface/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> USummonGameplayAbility::CalculateMinionSpawnLocation()
{
	TArray<FVector> ChosenSpawnLocations;
	AActor* Summoner = GetAvatarActorFromActorInfo();
	FVector Origin = Summoner->GetActorLocation();
	FVector Forward = Summoner->GetActorForwardVector();
	int32 MinionThreadHold = ICombatInterface::Execute_GetMinionThreadHold(Summoner);
	float DeltaSpread = SpawnWidthThreadHold / MinionThreadHold;

	float AngleToRotate = SpawnWidthThreadHold / 2;
	FVector LeftAngle = Forward.RotateAngleAxis(-AngleToRotate, FVector::UpVector);

	for (int32 i = 0; i < MinionThreadHold; i++)
	{
		FVector Direction = LeftAngle.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Origin + Direction * FMath::FRandRange(MinRadius, MaxRadius);
		ChosenSpawnLocations.AddUnique(ChosenSpawnLocation);
		UKismetSystemLibrary::DrawDebugSphere(Summoner, ChosenSpawnLocation, 10, 5.f, FColor::Green, 2.f, 1.f);
	}


	return ChosenSpawnLocations;
}
