// No Copyright.

#pragma once

#include "Data/FPSPlayerWeaponData.h"
#include "FPSPlayerTypes.generated.h"

UENUM(BlueprintType)
enum class ETurnInPlaceStatus: uint8
{
	Right UMETA(DisplayName = "Turning Right"),
	Left UMETA(DisplayName = "Turning Left"),
	NotTurning UMETA(DisplayName = "Not Turning")
};

struct FTurnInPlaceParameters
{
	float AimOffsetYaw;
	float MovementOffsetYaw;
	ETurnInPlaceStatus TurnInPlaceStatus = ETurnInPlaceStatus::NotTurning;
};

struct FCurrentAnimSets
{
	FPlayerAnimSets FirstPersonAnimSets;
	FPlayerAnimSets ThirdPersonAnimSets;
};
