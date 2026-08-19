// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/FPSPlayerInterface.h"
#include "FPSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UFPSPlayerCombat;
/**
 * 
 */
UCLASS()
class FPS_API AFPSPlayerCharacter : public ACharacter, public IFPSPlayerInterface
{
	GENERATED_BODY()
	
public:
	AFPSPlayerCharacter();
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
#pragma region Player Interface
	virtual FName GetWeaponGripPoint_Implementation(const FGameplayTag& WeaponType) const override;
#pragma endregion 
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "FPS|Mesh")
	TObjectPtr<USkeletalMeshComponent> PlayerMesh1P;
	
	UPROPERTY(VisibleAnywhere, Category = "FPS|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = "FPS|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere, Category = "FPS|Combat")
	TObjectPtr<UFPSPlayerCombat> PlayerCombat;
	
private:
	void Input_CycleWeapon();
	
	void Input_AimWeaponPressed();
	void Input_AimWeaponReleased();
	
	void Input_FireWeaponPressed();
	void Input_FireWeaponReleased();
	
	void Input_ReloadWeapon();
};
