// No Copyright.

#pragma once

#include "CoreMinimal.h"

class AFPSPlayerCharacter;
struct FPlayerAnimSets;
/**
 * 
 */
class FPS_API FPSPlayerAnimUtils
{
public:
	static float GetMappedAimPitchRotation(const AFPSPlayerCharacter* PlayerCharacter);
	static FTransform CalculateLeftHandIKEffectorTransform(const AFPSPlayerCharacter* PlayerCharacter);
	static FPlayerAnimSets GetFirstPersonAnimSets(const AFPSPlayerCharacter* PlayerCharacter);
	static FPlayerAnimSets GetThirdPersonAnimSets(const AFPSPlayerCharacter* PlayerCharacter);
};
