// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "FPSPlayerWeaponData.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UFPSPlayerWeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Weapon", meta = (Categories = "Weapon.WeaponType"))
	TMap<FGameplayTag, FName> WeaponGripPoints;
};
