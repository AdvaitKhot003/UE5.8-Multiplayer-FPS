// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "FPSPlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSPlayerWeapon : public AActor
{
	GENERATED_BODY()

public:
	AFPSPlayerWeapon();
	
	virtual void OnRep_Instigator() override;
	
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh1P() const { return WeaponMesh1P; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh3P() const { return WeaponMesh3P; }
	FORCEINLINE FGameplayTag GetWeaponType() const { return WeaponType; }
	
	void AttachWeaponToOwningPawn();
	
	UFUNCTION(BlueprintPure)
	float GetAimFieldOfView() const;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Weapon", meta = (Categories = "Weapon.WeaponType"))
	FGameplayTag WeaponType;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "FPS|Mesh")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh1P;
	
	UPROPERTY(VisibleAnywhere, Category = "FPS|Mesh")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh3P;

	void SetWeaponVisibility(APawn* OwningPawn);
};
