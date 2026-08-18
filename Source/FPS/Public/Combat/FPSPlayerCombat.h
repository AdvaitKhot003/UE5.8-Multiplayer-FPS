// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSPlayerCombat.generated.h"

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
	
	void Initiate_CycleWeapon();
	
	void Initiate_AimWeaponPressed();
	void Initiate_AimWeaponReleased();

	void Initiate_FireWeaponPressed();
	void Initiate_FireWeaponReleased();

	void Initiate_ReloadWeapon();
	
protected:
	
private:
	
};
