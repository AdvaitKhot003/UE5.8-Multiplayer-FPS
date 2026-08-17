// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

class UFPSPlayerInputData;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class FPS_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFPSPlayerController();
	
	FORCEINLINE UFPSPlayerInputData* GetPlayerInputData() const { return PlayerInputData; }
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "FPS|Data")
	TObjectPtr<UFPSPlayerInputData> PlayerInputData;
	
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Move(const FInputActionValue& InputActionValue);
	
	void Input_JumpPressed();
	void Input_JumpReleased();
	
	void Input_CrouchPressed();
	void Input_CrouchReleased();
};
