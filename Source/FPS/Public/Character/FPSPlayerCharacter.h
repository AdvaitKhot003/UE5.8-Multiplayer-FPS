// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPlayerCharacter.generated.h"

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
	
public:	
	
};
