// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/FPSPlayerWeaponData.h"
#include "FPSPlayerAnimInstance.generated.h"

class AFPSPlayerCharacter;
class UFPSPlayerCombat;
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
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Animation")
	bool bCurrentEquippedWeapon;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|FABRIK")
	FTransform LeftHandIKEffectorTransform;
#pragma endregion
	
private:
	UPROPERTY(Transient)
	TObjectPtr<AFPSPlayerCharacter> PlayerCharacter;
	
	UPROPERTY(Transient)
	TObjectPtr<UFPSPlayerCombat> PlayerCombat;
	
#pragma region Game-thread cache
	bool bCachedAiming;
	bool bCachedCurrentEquippedWeapon;
	
	FPlayerAnimSets CachedFirstPersonAnimSets;
	FPlayerAnimSets CachedThirdPersonAnimSets;
	
	float CachedMappedAimPitchRotation;
	FTransform CachedLeftHandIKEffectorTransform;
#pragma endregion
	
	void UpdateAnimationData();
};
