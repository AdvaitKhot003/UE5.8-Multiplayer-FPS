// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FPSPlayerInputData.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class FPS_API UFPSPlayerInputData : public UDataAsset
{
	GENERATED_BODY()
	
public:
#pragma region Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IMC")
	TObjectPtr<UInputMappingContext> InputMappingContext;
#pragma endregion
	
#pragma region Input Actions - Locomotion
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Locomotion")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Locomotion")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Locomotion")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Locomotion")
	TObjectPtr<UInputAction> CrouchAction;
#pragma endregion
	
#pragma region Input Actions - Combat
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Combat")
	TObjectPtr<UInputAction> CycleWeaponAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Combat")
	TObjectPtr<UInputAction> AimWeaponAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Combat")
	TObjectPtr<UInputAction> FireWeaponAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Combat")
	TObjectPtr<UInputAction> ReloadWeaponAction;
#pragma endregion
};
