// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSPlayerCombat.generated.h"

class UFPSPlayerWeaponData;
class AFPSPlayerWeapon;
/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPS_API UFPSPlayerCombat : public UActorComponent
{
	GENERATED_BODY()

public:
	UFPSPlayerCombat();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FORCEINLINE UFPSPlayerWeaponData* GetPlayerWeaponData() const { return PlayerWeaponData; }
	
	void SpawnInventory();
	void DestroyInventory();
	
	void Initiate_CycleWeapon();
	
	void Initiate_AimWeaponPressed();
	void Initiate_AimWeaponReleased();

	void Initiate_FireWeaponPressed();
	void Initiate_FireWeaponReleased();

	void Initiate_ReloadWeapon();
	
protected:
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Weapon")
	TObjectPtr<UFPSPlayerWeaponData> PlayerWeaponData;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Weapon")
	TSubclassOf<AFPSPlayerWeapon> DefaultWeaponClass;
	
	AFPSPlayerWeapon* SpawnWeapon(const TSubclassOf<AFPSPlayerWeapon> WeaponClass) const;
};
