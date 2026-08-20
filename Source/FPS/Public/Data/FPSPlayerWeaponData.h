// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "FPSPlayerWeaponData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerAnimSets
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Animation.AnimSequence"))
	TMap<FGameplayTag, TObjectPtr<UAnimSequence>> AnimSequences;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Animation.BlendSpace"))
	TMap<FGameplayTag, TObjectPtr<UBlendSpace>> BlendSpaces;
};

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
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Animation", meta = (Categories = "Weapon.WeaponType"))
	TMap<FGameplayTag, FPlayerAnimSets> FirstPersonAnimSets;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Animation", meta = (Categories = "Weapon.WeaponType"))
	TMap<FGameplayTag, FPlayerAnimSets> ThirdPersonAnimSets;
};
