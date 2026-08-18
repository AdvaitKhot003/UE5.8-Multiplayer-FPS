// No Copyright.

#include "Weapon/FPSPlayerWeapon.h"
#include "Tags/FPSPlayerGameplayTags.h"

AFPSPlayerWeapon::AFPSPlayerWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	
	WeaponMesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh1PComp"));
	SetRootComponent(WeaponMesh1P);
	WeaponMesh1P->SetHiddenInGame(true);
	WeaponMesh1P->SetCastShadow(false);
	WeaponMesh1P->SetReceivesDecals(false);
	WeaponMesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	
	WeaponMesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh3PComp"));
	WeaponMesh3P->SetupAttachment(GetRootComponent());
	WeaponMesh3P->SetHiddenInGame(true);
	WeaponMesh3P->SetCastShadow(true);
	WeaponMesh3P->SetReceivesDecals(false);
	WeaponMesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	
	WeaponType = WeaponTags::Weapon_WeaponType_None;
}

void AFPSPlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
