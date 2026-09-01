// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Types/FPSPlayerTypes.h"
#include "FPSPlayerAnimInstance.generated.h"

class AFPSPlayerCharacter;
class UFPSPlayerCombat;
class UFPSPlayerWeaponData;
class UCharacterMovementComponent;
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
	bool bHasCurrentEquippedWeapon;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Animation")
	float MappedAimPitchRotation;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|FABRIK")
	FTransform LeftHandIKEffectorTransform;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|TurnInPlace")
	float AimOffsetYaw;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Strafing")
	float MovementOffsetYaw;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|TurnInPlace")
	ETurnInPlaceStatus TurnInPlaceStatus = ETurnInPlaceStatus::NotTurning;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Locomotion")
	float GroundSpeed;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Locomotion")
	bool bHasCurrentAcceleration;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Locomotion")
	bool bIsCrouching;
#pragma endregion
	
private:
	UPROPERTY(Transient)
	TObjectPtr<AFPSPlayerCharacter> PlayerCharacter;
	
	UPROPERTY(Transient)
	TObjectPtr<UFPSPlayerCombat> PlayerCombat;
	
	UPROPERTY(Transient)
	TObjectPtr<UFPSPlayerWeaponData> PlayerWeaponData;
	
	UPROPERTY(Transient)
	UCharacterMovementComponent* PlayerCharacterMovement;
	
#pragma region Game-thread cache
	FPlayerAnimSets CachedFirstPersonAnimSets;
	FPlayerAnimSets CachedThirdPersonAnimSets;
	
	FGameplayTag CachedEquippedWeaponType;
	
	bool bCachedAiming;
	
	bool bCachedCurrentEquippedWeapon;
	
	float CachedMappedAimPitchRotation;
	
	FTransform CachedLeftHandIKEffectorTransform;
	
	float CachedAimOffsetYaw;
	float CachedMovementOffsetYaw;
	ETurnInPlaceStatus CachedTurnInPlaceStatus = ETurnInPlaceStatus::NotTurning;
	
	FRotator InitialAimRotation;
	float InterpAimOffsetYaw;
	ETurnInPlaceStatus CurrentTurnInPlaceStatus = ETurnInPlaceStatus::NotTurning;
	
	float CachedGroundSpeed;
	
	bool bCachedHasCurrentAcceleration;
	
	bool bCachedIsCrouching;
#pragma endregion
	
	void UpdateAnimationData(float DeltaSeconds);
	
	FCurrentAnimSets GetCurrentAnimSets() const;
	
	float GetMappedAimPitchRotation() const;
	
	FTransform CalculateLeftHandIKEffectorTransform() const;
	
	FTurnInPlaceParameters CalculateTurnInPlaceParameters(float DeltaSeconds);
	void TurnInPlace(float DeltaSeconds, FTurnInPlaceParameters& Parameters);
};
