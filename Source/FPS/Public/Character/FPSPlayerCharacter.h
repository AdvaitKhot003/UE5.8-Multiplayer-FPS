// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UFPSPlayerCombat;
/**
 * 
 */
UCLASS()
class FPS_API AFPSPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	AFPSPlayerCharacter();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
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
	
};
