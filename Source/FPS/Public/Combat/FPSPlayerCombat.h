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
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	FORCEINLINE UFPSPlayerWeaponData* GetPlayerWeaponData() const { return PlayerWeaponData; }
	FORCEINLINE AFPSPlayerWeapon* GetCurrentEquippedWeapon() const { return CurrentEquippedWeapon; }
	
	void SpawnInventory();
	void DestroyInventory();
	void EquipWeapon(AFPSPlayerWeapon* Weapon);
	
#pragma region CycleWeapon
	void Initiate_CycleWeapon();
#pragma endregion
	
#pragma region AimWeapon
	void Initiate_AimWeaponPressed();
	void Initiate_AimWeaponReleased();
	
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "FPS|Weapon")
	bool bAiming;
#pragma endregion
	
#pragma region FireWeapon
	void Initiate_FireWeaponPressed();
	void Initiate_FireWeaponReleased();
#pragma endregion

#pragma region ReloadWeapon
	void Initiate_ReloadWeapon();
#pragma endregion
	
protected:
	UPROPERTY(Transient, BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentEquippedWeapon, Category = "FPS|Weapon")
	TObjectPtr<AFPSPlayerWeapon> CurrentEquippedWeapon;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Weapon")
	TObjectPtr<UFPSPlayerWeaponData> PlayerWeaponData;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Weapon")
	TArray<TSubclassOf<AFPSPlayerWeapon>> DefaultWeaponClasses;
	
	UPROPERTY(Transient, Replicated)
	TArray<AFPSPlayerWeapon*> Inventory;
	
	UFUNCTION()
	void OnRep_CurrentEquippedWeapon(AFPSPlayerWeapon* PreviousEquippedWeapon);
	
	AFPSPlayerWeapon* SpawnWeapon(const TSubclassOf<AFPSPlayerWeapon> WeaponClass) const;
	
#pragma region AimWeapon
	UFUNCTION(Server, Reliable)
	void Server_AimWeapon(bool bPressed);
	
	void Local_AimWeapon(bool bPressed);
#pragma endregion
};
