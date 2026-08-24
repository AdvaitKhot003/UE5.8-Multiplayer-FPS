// No Copyright.

#include "Animation/FPSPlayerAnimInstance.h"
#include "Character/FPSPlayerCharacter.h"
#include "Combat/FPSPlayerCombat.h"
#include "Weapon/FPSPlayerWeapon.h"

void UFPSPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	PlayerCharacter = Cast<AFPSPlayerCharacter>(TryGetPawnOwner());
	if (IsValid(PlayerCharacter))
	{
		PlayerCombat = PlayerCharacter->GetPlayerCombat();
		if (!IsValid(PlayerCombat)) return;
		PlayerWeaponData = PlayerCombat->GetPlayerWeaponData();
	}
}

void UFPSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	UpdateAnimationData(DeltaSeconds);
}

void UFPSPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	CurrentFirstPersonAnimSets = CachedFirstPersonAnimSets;
	CurrentThirdPersonAnimSets = CachedThirdPersonAnimSets;
	
	bIsAiming = bCachedAiming;
	
	bHasCurrentEquippedWeapon = bCachedCurrentEquippedWeapon;
	
	MappedAimPitchRotation = CachedMappedAimPitchRotation;
	
	LeftHandIKEffectorTransform = CachedLeftHandIKEffectorTransform;
}

void UFPSPlayerAnimInstance::UpdateAnimationData(float DeltaSeconds)
{
	if (IsValid(PlayerCharacter) && IsValid(PlayerCombat) && IsValid(PlayerWeaponData))
	{
		const FCurrentAnimSets CurrentAnimSets = GetCurrentAnimSets();
		CachedFirstPersonAnimSets = CurrentAnimSets.FirstPersonAnimSets;
		CachedThirdPersonAnimSets = CurrentAnimSets.ThirdPersonAnimSets;
		
		bCachedAiming = PlayerCombat->bAiming;
		
		bCachedCurrentEquippedWeapon = IsValid(PlayerCombat->GetCurrentEquippedWeapon());
		
		CachedMappedAimPitchRotation = GetMappedAimPitchRotation();
		
		CachedLeftHandIKEffectorTransform = CalculateLeftHandIKEffectorTransform();
	}
}

FCurrentAnimSets UFPSPlayerAnimInstance::GetCurrentAnimSets() const
{
	if (IsValid(PlayerCharacter) && IsValid(PlayerCombat) && IsValid(PlayerWeaponData))
	{
		const AFPSPlayerWeapon* CurrentEquippedWeapon = PlayerCombat->GetCurrentEquippedWeapon();
		if (!IsValid(CurrentEquippedWeapon)) return {};
		
		const FGameplayTag EquippedWeaponType = CurrentEquippedWeapon->GetWeaponType();
		if (!EquippedWeaponType.IsValid()) return {};
		
		FCurrentAnimSets AnimSets;
		AnimSets.FirstPersonAnimSets = PlayerWeaponData->FirstPersonAnimSets.FindChecked(EquippedWeaponType);
		AnimSets.ThirdPersonAnimSets = PlayerWeaponData->ThirdPersonAnimSets.FindChecked(EquippedWeaponType);
		
		return AnimSets;
	}
	return {};
}

float UFPSPlayerAnimInstance::GetMappedAimPitchRotation() const
{
	if (IsValid(PlayerCharacter))
	{
		float AimPitchRotation = PlayerCharacter->GetBaseAimRotation().Pitch;
		
		if (AimPitchRotation > 90 && !PlayerCharacter->IsLocallyControlled())
		{
			const FVector2D InRange(270.f, 360.f);
			const FVector2D OutRange(-90.f, 0.f);
			AimPitchRotation = FMath::GetMappedRangeValueClamped(InRange, OutRange, AimPitchRotation);
		}
		
		return AimPitchRotation;
	}
	return 0.f;
}

FTransform UFPSPlayerAnimInstance::CalculateLeftHandIKEffectorTransform() const
{
	if (IsValid(PlayerCharacter) && IsValid(PlayerCombat) && IsValid(PlayerWeaponData))
	{
		const AFPSPlayerWeapon* CurrentEquippedWeapon = PlayerCombat->GetCurrentEquippedWeapon();
		if (!IsValid(CurrentEquippedWeapon)) return FTransform::Identity;
		
		const FGameplayTag EquippedWeaponType = CurrentEquippedWeapon->GetWeaponType();
		if (!EquippedWeaponType.IsValid()) return FTransform::Identity;
		
		const USkeletalMeshComponent* WeaponMesh3P = CurrentEquippedWeapon->GetWeaponMesh3P();
		if (!IsValid(WeaponMesh3P)) return FTransform::Identity;
		
		const USkeletalMeshComponent* PlayerMesh3P = PlayerCharacter->GetMesh();
		if (!IsValid(PlayerMesh3P)) return FTransform::Identity;
		
		const FName LeftHandIKSocket = PlayerWeaponData->LeftHandIKSockets.FindChecked(EquippedWeaponType);
		const FTransform LeftHandIKSocketTransform = WeaponMesh3P->GetSocketTransform(LeftHandIKSocket, RTS_World);
		
		FVector OutLocation;
		FRotator OutRotation;
		
		PlayerMesh3P->TransformToBoneSpace
		(
			"hand_r",
			LeftHandIKSocketTransform.GetLocation(),
			LeftHandIKSocketTransform.GetRotation().Rotator(),
			OutLocation,
			OutRotation
		);
		
		return FTransform(OutRotation.Quaternion(), OutLocation);
	}
	return FTransform::Identity;
}
