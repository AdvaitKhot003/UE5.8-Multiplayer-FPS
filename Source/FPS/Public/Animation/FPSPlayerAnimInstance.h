// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/FPSPlayerWeaponData.h"
#include "FPSPlayerAnimInstance.generated.h"

class AFPSPlayerCharacter;
/**
 * 
 */
UCLASS()
class FPS_API UFPSPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
#pragma region Animation-thread state
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Animation")
	FPlayerAnimSets CurrentFirstPersonAnimSets;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Animation")
	FPlayerAnimSets CurrentThirdPersonAnimSets;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Animation")
	bool bIsAiming;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Animation")
	float MappedAimPitchRotation;
#pragma endregion
	
private:
	UPROPERTY()
	TObjectPtr<AFPSPlayerCharacter> PlayerCharacter;
	
#pragma region Game-thread cache
	FPlayerAnimSets CachedFirstPersonAnimSets;
	FPlayerAnimSets CachedThirdPersonAnimSets;
	bool bCachedAiming;
	float CachedMappedAimPitchRotation;
#pragma endregion
	
	void GetCurrentAnimSets();
};
