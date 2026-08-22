// No Copyright.

#include "Animation/FPSPlayerAnimUtils.h"
#include "Character/FPSPlayerCharacter.h"
#include "Combat/FPSPlayerCombat.h"
#include "Data/FPSPlayerWeaponData.h"
#include "Weapon/FPSPlayerWeapon.h"

float FPSPlayerAnimUtils::GetMappedAimPitchRotation(const AFPSPlayerCharacter* PlayerCharacter)
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

FTransform FPSPlayerAnimUtils::CalculateLeftHandIKEffectorTransform(const AFPSPlayerCharacter* PlayerCharacter)
{
	if (IsValid(PlayerCharacter))
	{
		const UFPSPlayerCombat* PlayerCombat = PlayerCharacter->GetPlayerCombat();
		if (!IsValid(PlayerCombat)) return FTransform::Identity;
	
		const UFPSPlayerWeaponData* PlayerWeaponData = PlayerCombat->GetPlayerWeaponData();
		if (!IsValid(PlayerWeaponData)) return FTransform::Identity;
	
		const AFPSPlayerWeapon* CurrentEquippedWeapon = PlayerCombat->GetCurrentEquippedWeapon();
		if (!IsValid(CurrentEquippedWeapon)) return FTransform::Identity;
	
		const FGameplayTag EquippedWeaponType = CurrentEquippedWeapon->GetWeaponType();
		if (!EquippedWeaponType.IsValid()) return FTransform::Identity;
	
		const USkeletalMeshComponent* WeaponMesh3P = CurrentEquippedWeapon->GetWeaponMesh3P();
		if (!IsValid(WeaponMesh3P)) return FTransform::Identity;
	
		const FName LeftHandIKSocket = PlayerWeaponData->LeftHandIKSockets.FindChecked(EquippedWeaponType);
		const FTransform LeftHandIKSocketTransform = WeaponMesh3P->GetSocketTransform(LeftHandIKSocket, RTS_World);
	
		FVector OutLocation;
		FRotator OutRotation;
	
		PlayerCharacter->GetMesh()->TransformToBoneSpace
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

FPlayerAnimSets FPSPlayerAnimUtils::GetFirstPersonAnimSets(const AFPSPlayerCharacter* PlayerCharacter)
{
	if (IsValid(PlayerCharacter))
	{
		const UFPSPlayerCombat* PlayerCombat = PlayerCharacter->GetPlayerCombat();
		if (!IsValid(PlayerCombat)) return {};
	
		const UFPSPlayerWeaponData* PlayerWeaponData = PlayerCombat->GetPlayerWeaponData();
		if (!IsValid(PlayerWeaponData)) return {};
		
		const AFPSPlayerWeapon* CurrentEquippedWeapon = PlayerCombat->GetCurrentEquippedWeapon();
		if (!IsValid(CurrentEquippedWeapon)) return {};
		
		const FGameplayTag EquippedWeaponType = CurrentEquippedWeapon->GetWeaponType();
		if (!EquippedWeaponType.IsValid()) return {};
		
		return PlayerWeaponData->FirstPersonAnimSets.FindChecked(EquippedWeaponType);
	}
	return {};
}

FPlayerAnimSets FPSPlayerAnimUtils::GetThirdPersonAnimSets(const AFPSPlayerCharacter* PlayerCharacter)
{
	if (IsValid(PlayerCharacter))
	{
		const UFPSPlayerCombat* PlayerCombat = PlayerCharacter->GetPlayerCombat();
		if (!IsValid(PlayerCombat)) return {};
	
		const UFPSPlayerWeaponData* PlayerWeaponData = PlayerCombat->GetPlayerWeaponData();
		if (!IsValid(PlayerWeaponData)) return {};
		
		const AFPSPlayerWeapon* CurrentEquippedWeapon = PlayerCombat->GetCurrentEquippedWeapon();
		if (!IsValid(CurrentEquippedWeapon)) return {};
		
		const FGameplayTag EquippedWeaponType = CurrentEquippedWeapon->GetWeaponType();
		if (!EquippedWeaponType.IsValid()) return {};
		
		return PlayerWeaponData->ThirdPersonAnimSets.FindChecked(EquippedWeaponType);
	}
	return {};
}
