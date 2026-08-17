// No Copyright.

#include "Player/FPSPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Data/FPSPlayerInputData.h"
#include "Input/FPSPlayerEnhancedInput.h"
#include "Character/FPSPlayerCharacter.h"

AFPSPlayerController::AFPSPlayerController()
{
	bReplicates = true;
}

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsLocalController()) return;
	
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem);
	check(PlayerInputData);
	check(PlayerInputData->InputMappingContext);
	Subsystem->AddMappingContext(PlayerInputData->InputMappingContext, 0);
}

void AFPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(PlayerInputData);
	UFPSPlayerEnhancedInput* PlayerEnhancedInput = CastChecked<UFPSPlayerEnhancedInput>(InputComponent);
	
	const UInputAction* LookAction = PlayerInputData->LookAction;
	check(LookAction);
	PlayerEnhancedInput->BindAction(
		LookAction, ETriggerEvent::Triggered,
		this, &ThisClass::Input_Look);
	
	const UInputAction* MoveAction = PlayerInputData->MoveAction;
	check(MoveAction);
	PlayerEnhancedInput->BindAction(
		MoveAction, ETriggerEvent::Triggered,
		this, &ThisClass::Input_Move);
	
	const UInputAction* JumpAction = PlayerInputData->JumpAction;
	check(JumpAction);
	PlayerEnhancedInput->BindAction(
		JumpAction, ETriggerEvent::Started,
		this, &ThisClass::Input_JumpPressed);
	
	PlayerEnhancedInput->BindAction(
		JumpAction, ETriggerEvent::Completed,
		this, &ThisClass::Input_JumpReleased);
	
	const UInputAction* CrouchAction = PlayerInputData->CrouchAction;
	check(CrouchAction);
	PlayerEnhancedInput->BindAction(
		CrouchAction, ETriggerEvent::Started,
		this, &ThisClass::Input_CrouchPressed);
	
	PlayerEnhancedInput->BindAction(
		CrouchAction, ETriggerEvent::Completed,
		this, &ThisClass::Input_CrouchReleased);
}

void AFPSPlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	
	if (!FMath::IsNearlyZero(InputAxisValue.X))
	{
		AddYawInput(InputAxisValue.X);
	}
	
	if (!FMath::IsNearlyZero(InputAxisValue.Y))
	{
		AddPitchInput(InputAxisValue.Y);
	}
}

void AFPSPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	APawn* ControlledPawn = GetPawn<APawn>();
	if (!IsValid(ControlledPawn)) return;
	
	if (!FMath::IsNearlyZero(InputAxisValue.X))
	{
		const FVector RightDirection = YawRotation.RotateVector(FVector::RightVector);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisValue.X);
	}
	
	if (!FMath::IsNearlyZero(InputAxisValue.Y))
	{
		const FVector ForwardDirection = YawRotation.RotateVector(FVector::ForwardVector);
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
	}
}

void AFPSPlayerController::Input_JumpPressed()
{
	AFPSPlayerCharacter* PlayerCharacter = Cast<AFPSPlayerCharacter>(GetCharacter());
	if (!IsValid(PlayerCharacter)) return;
	
	PlayerCharacter->Jump();
}

void AFPSPlayerController::Input_JumpReleased()
{
	AFPSPlayerCharacter* PlayerCharacter = Cast<AFPSPlayerCharacter>(GetCharacter());
	if (!IsValid(PlayerCharacter)) return;
	
	PlayerCharacter->StopJumping();
}

void AFPSPlayerController::Input_CrouchPressed()
{
	AFPSPlayerCharacter* PlayerCharacter = Cast<AFPSPlayerCharacter>(GetCharacter());
	if (!IsValid(PlayerCharacter)) return;
	
	PlayerCharacter->Crouch();
}

void AFPSPlayerController::Input_CrouchReleased()
{
	AFPSPlayerCharacter* PlayerCharacter = Cast<AFPSPlayerCharacter>(GetCharacter());
	if (!IsValid(PlayerCharacter)) return;
	
	PlayerCharacter->UnCrouch();
}
