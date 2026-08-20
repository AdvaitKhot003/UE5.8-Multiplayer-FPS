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
}

void UFPSPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	CurrentFirstPersonAnimSets = CachedFirstPersonAnimSets;
	CurrentThirdPersonAnimSets = CachedThirdPersonAnimSets;
	bIsAiming = bCachedAiming;
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
}
