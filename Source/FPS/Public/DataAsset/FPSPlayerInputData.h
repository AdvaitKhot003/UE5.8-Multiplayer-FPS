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
	/** Input Mapping Context */
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IMC")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	/** Input Actions - Locomotion */
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Locomotion")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Locomotion")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Locomotion")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|IA|Locomotion")
	TObjectPtr<UInputAction> CrouchAction;
};
