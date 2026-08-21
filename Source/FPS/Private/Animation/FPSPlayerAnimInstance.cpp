// No Copyright.

#include "Animation/FPSPlayerAnimInstance.h"
#include "Character/FPSPlayerCharacter.h"
#include "Combat/FPSPlayerCombat.h"
#include "Weapon/FPSPlayerWeapon.h"

void UFPSPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	PlayerCharacter = Cast<AFPSPlayerCharacter>(TryGetPawnOwner());
}

void UFPSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	GetCurrentAnimSets();
	UpdateLeftHandIKEffectorTransform();
}

void UFPSPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	CurrentFirstPersonAnimSets = CachedFirstPersonAnimSets;
	CurrentThirdPersonAnimSets = CachedThirdPersonAnimSets;
	bIsAiming = bCachedAiming;
	MappedAimPitchRotation = CachedMappedAimPitchRotation;
	LeftHandIKEffectorTransform = CachedLeftHandIKEffectorTransform;
}

void UFPSPlayerAnimInstance::GetCurrentAnimSets()
{
	if (!IsValid(PlayerCharacter)) return;
	
	const UFPSPlayerCombat* PlayerCombat = PlayerCharacter->GetPlayerCombat();
	if (!IsValid(PlayerCombat)) return;
	
	const AFPSPlayerWeapon* CurrentEquippedWeapon = PlayerCombat->GetCurrentEquippedWeapon();
	if (!IsValid(CurrentEquippedWeapon)) return;
	
	UFPSPlayerWeaponData* PlayerWeaponData = PlayerCombat->GetPlayerWeaponData();
	if (!IsValid(PlayerWeaponData)) return;
	
	const FGameplayTag EquippedWeaponType = CurrentEquippedWeapon->GetWeaponType();
	if (!EquippedWeaponType.IsValid()) return;
	
	CachedFirstPersonAnimSets = PlayerWeaponData->FirstPersonAnimSets.FindChecked(EquippedWeaponType);
	CachedThirdPersonAnimSets = PlayerWeaponData->ThirdPersonAnimSets.FindChecked(EquippedWeaponType);
	bCachedAiming = PlayerCombat->bAiming;
	CachedMappedAimPitchRotation = PlayerCharacter->GetMappedAimPitchRotation();
}

void UFPSPlayerAnimInstance::UpdateLeftHandIKEffectorTransform()
{
	if (!IsValid(PlayerCharacter)) return;
	
	const UFPSPlayerCombat* PlayerCombat = PlayerCharacter->GetPlayerCombat();
	if (!IsValid(PlayerCombat)) return;
	
	const AFPSPlayerWeapon* CurrentEquippedWeapon = PlayerCombat->GetCurrentEquippedWeapon();
	if (!IsValid(CurrentEquippedWeapon)) return;
	
	const USkeletalMeshComponent* WeaponMesh3P = CurrentEquippedWeapon->GetWeaponMesh3P();
	if (!IsValid(WeaponMesh3P)) return;
	
	const UFPSPlayerWeaponData* PlayerWeaponData = PlayerCombat->GetPlayerWeaponData();
	if (!IsValid(PlayerWeaponData)) return;
	
	const FName LeftHandIKSocket = PlayerWeaponData->LeftHandIKSockets.FindChecked(CurrentEquippedWeapon->GetWeaponType());
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
	
	CachedLeftHandIKEffectorTransform.SetLocation(OutLocation);
	CachedLeftHandIKEffectorTransform.SetRotation(OutRotation.Quaternion());
}
