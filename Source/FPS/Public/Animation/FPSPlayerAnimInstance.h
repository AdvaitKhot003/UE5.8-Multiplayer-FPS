// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/FPSPlayerWeaponData.h"
#include "FPSPlayerAnimInstance.generated.h"

class AFPSPlayerCharacter;
/**
 * 
 */
UCLASS()
class FPS_API UFPSPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
#pragma region Animation-thread state
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Animation")
	FPlayerAnimSets CurrentFirstPersonAnimSets;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPS|Animation")
	FPlayerAnimSets CurrentThirdPersonAnimSets;
#pragma endregion
	
private:
	UPROPERTY()
	AFPSPlayerCharacter* PlayerCharacter;
	
#pragma region Game-thread cache
	FPlayerAnimSets CachedFirstPersonAnimSets;
	FPlayerAnimSets CachedThirdPersonAnimSets;
#pragma endregion
	
	void GetCurrentAnimSets();
};
