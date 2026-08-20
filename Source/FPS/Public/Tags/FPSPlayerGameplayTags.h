// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace WeaponTags
{
#pragma region WeaponTypes
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_WeaponType_None);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_WeaponType_Pistol);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_WeaponType_Rifle);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_WeaponType_Shotgun);
#pragma endregion
}

namespace AnimationTags
{
#pragma region AnimSequences
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AnimSequence_Idle);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AnimSequence_AimIdle);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AnimSequence_Crouch);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AnimSequence_Sprint);
#pragma endregion
	
#pragma region BlendSpaces
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BlendSpace_AimOffset_Hip);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BlendSpace_AimOffset_Aim);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BlendSpace_Strafe_Standing);
	FPS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(BlendSpace_Strafe_Crouching);
#pragma endregion
}
