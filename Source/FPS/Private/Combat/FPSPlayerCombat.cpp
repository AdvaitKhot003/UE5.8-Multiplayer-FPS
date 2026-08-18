// No Copyright.

#include "Combat/FPSPlayerCombat.h"

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
