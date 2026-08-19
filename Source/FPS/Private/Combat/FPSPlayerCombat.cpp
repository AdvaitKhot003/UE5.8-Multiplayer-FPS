// No Copyright.

#include "Combat/FPSPlayerCombat.h"
#include "Weapon/FPSPlayerWeapon.h"

UFPSPlayerCombat::UFPSPlayerCombat()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UFPSPlayerCombat::BeginPlay()
{
	Super::BeginPlay();
	
}

void UFPSPlayerCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UFPSPlayerCombat::SpawnInventory()
{
	check(DefaultWeaponClass);
	AFPSPlayerWeapon* SpawnedWeapon = SpawnWeapon(DefaultWeaponClass);
}

void UFPSPlayerCombat::DestroyInventory()
{
	
}

AFPSPlayerWeapon* UFPSPlayerCombat::SpawnWeapon(const TSubclassOf<AFPSPlayerWeapon> WeaponClass) const
{
	AActor* OwningActor = GetOwner();
	if (!IsValid(OwningActor)) return nullptr;
	if (!OwningActor->HasAuthority()) return nullptr;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwningActor;
	SpawnParams.Instigator = Cast<APawn>(OwningActor);
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	return GetWorld()->SpawnActor<AFPSPlayerWeapon>(WeaponClass, SpawnParams);
}

void UFPSPlayerCombat::Initiate_CycleWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("CycleWeapon"));
}

void UFPSPlayerCombat::Initiate_AimWeaponPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("AimWeaponPressed"));
}

void UFPSPlayerCombat::Initiate_AimWeaponReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("AimWeaponReleased"));
}

void UFPSPlayerCombat::Initiate_FireWeaponPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("FireWeaponPressed"));
}

void UFPSPlayerCombat::Initiate_FireWeaponReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("FireWeaponReleased"));
}

void UFPSPlayerCombat::Initiate_ReloadWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("ReloadWeapon"));
}
