// No Copyright.

#include "Weapon/FPSPlayerWeapon.h"
#include "Tags/FPSPlayerGameplayTags.h"
#include "Interface/FPSPlayerInterface.h"
#include "Combat/FPSPlayerCombat.h"

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

void AFPSPlayerWeapon::OnRep_Instigator()
{
	Super::OnRep_Instigator();
	
	const APawn* OwningPawn = GetInstigator();
	if (!IsValid(OwningPawn)) return;
	
	const UFPSPlayerCombat* PlayerCombat = OwningPawn->FindComponentByClass<UFPSPlayerCombat>();
	if (!IsValid(PlayerCombat)) return;
	
	AFPSPlayerWeapon* CurrentEquippedWeapon = PlayerCombat->GetCurrentEquippedWeapon();
	if (CurrentEquippedWeapon != this) return;
	CurrentEquippedWeapon->AttachWeaponToOwningPawn();
}

void AFPSPlayerWeapon::AttachWeaponToOwningPawn()
{
	APawn* OwningPawn = GetInstigator();
	if (!IsValid(OwningPawn) || !OwningPawn->Implements<UFPSPlayerInterface>()) return;
	
	SetWeaponVisibility(OwningPawn);
	
	const FName WeaponGripPoint = IFPSPlayerInterface::Execute_GetWeaponGripPoint(OwningPawn, WeaponType);
	USkeletalMeshComponent* PlayerMesh1P = IFPSPlayerInterface::Execute_GetPlayerMesh1P(OwningPawn);
	USkeletalMeshComponent* PlayerMesh3P = IFPSPlayerInterface::Execute_GetPlayerMesh3P(OwningPawn);
	
	WeaponMesh1P->AttachToComponent(PlayerMesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponGripPoint);
	WeaponMesh3P->AttachToComponent(PlayerMesh3P, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponGripPoint);
}

void AFPSPlayerWeapon::SetWeaponVisibility(APawn* OwningPawn)
{
	if (OwningPawn->IsLocallyControlled())
	{
		WeaponMesh1P->SetHiddenInGame(false);
		WeaponMesh3P->SetHiddenInGame(true);
	}
	else
	{
		WeaponMesh1P->SetHiddenInGame(true);
		WeaponMesh3P->SetHiddenInGame(false);
	}
}
