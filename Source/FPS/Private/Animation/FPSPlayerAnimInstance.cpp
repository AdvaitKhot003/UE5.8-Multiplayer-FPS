// No Copyright.

#include "Animation/FPSPlayerAnimInstance.h"
#include "Animation/FPSPlayerAnimUtils.h"
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
	}
}

void UFPSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	UpdateAnimationData();
}

void UFPSPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	bIsAiming = bCachedAiming;
	bCurrentEquippedWeapon = bCachedCurrentEquippedWeapon;
	
	CurrentFirstPersonAnimSets = CachedFirstPersonAnimSets;
	CurrentThirdPersonAnimSets = CachedThirdPersonAnimSets;
	
	MappedAimPitchRotation = CachedMappedAimPitchRotation;
	LeftHandIKEffectorTransform = CachedLeftHandIKEffectorTransform;
}

void UFPSPlayerAnimInstance::UpdateAnimationData()
{
	if (IsValid(PlayerCharacter) && IsValid(PlayerCombat))
	{
		bCachedAiming = PlayerCombat->bAiming;
		bCachedCurrentEquippedWeapon = IsValid(PlayerCombat->GetCurrentEquippedWeapon());
		CachedFirstPersonAnimSets = FPSPlayerAnimUtils::GetFirstPersonAnimSets(PlayerCharacter);
		CachedThirdPersonAnimSets = FPSPlayerAnimUtils::GetThirdPersonAnimSets(PlayerCharacter);
		CachedMappedAimPitchRotation = FPSPlayerAnimUtils::GetMappedAimPitchRotation(PlayerCharacter);
		CachedLeftHandIKEffectorTransform = FPSPlayerAnimUtils::CalculateLeftHandIKEffectorTransform(PlayerCharacter);
	};
}
