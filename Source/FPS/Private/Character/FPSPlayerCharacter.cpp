// No Copyright.

#include "Character/FPSPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Combat/FPSPlayerCombat.h"
#include "Player/FPSPlayerController.h"
#include "Input/FPSPlayerEnhancedInput.h"
#include "Data/FPSPlayerInputData.h"
#include "Data/FPSPlayerWeaponData.h"

AFPSPlayerCharacter::AFPSPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 0.f;
	SpringArm->SocketOffset = FVector::ZeroVector;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 20.f;
	SpringArm->CameraLagMaxDistance = 10.f;
	SpringArm->CameraLagMaxTimeStep = 0.0166667f;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComp"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	PlayerMesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh1PComp"));
	PlayerMesh1P->SetupAttachment(FollowCamera);
	PlayerMesh1P->SetOnlyOwnerSee(true);
	PlayerMesh1P->SetOwnerNoSee(false);
	PlayerMesh1P->SetCastShadow(false);
	PlayerMesh1P->SetReceivesDecals(false);
	PlayerMesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	PlayerMesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	
	GetMesh()->SetOnlyOwnerSee(false);
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetCastShadow(true);
	GetMesh()->SetReceivesDecals(false);
	
	GetCharacterMovement()->MovementState.bCanCrouch = true;
	
	PlayerCombat = CreateDefaultSubobject<UFPSPlayerCombat>(TEXT("PlayerCombatComp"));
	PlayerCombat->SetIsReplicated(true);
}

void AFPSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	PlayerCombat->SpawnInventory();
}

void AFPSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

FName AFPSPlayerCharacter::GetWeaponGripPoint_Implementation(const FGameplayTag& WeaponType) const
{
	const UFPSPlayerWeaponData* PlayerWeaponData = PlayerCombat->GetPlayerWeaponData();
	check(PlayerWeaponData);
	return PlayerWeaponData->WeaponGripPoints.FindChecked(WeaponType);
}

void AFPSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	const AFPSPlayerController* PlayerController = Cast<AFPSPlayerController>(GetController());
	if (!IsValid(PlayerController)) return;
	
	const UFPSPlayerInputData* PlayerInputData = PlayerController->GetPlayerInputData();
	check(PlayerInputData);
	
	UFPSPlayerEnhancedInput* PlayerEnhancedInput = CastChecked<UFPSPlayerEnhancedInput>(PlayerInputComponent);
	
	const UInputAction* CycleWeaponAction = PlayerInputData->CycleWeaponAction;
	check(CycleWeaponAction);
	PlayerEnhancedInput->BindAction(
		CycleWeaponAction, ETriggerEvent::Started,
		this, &ThisClass::Input_CycleWeapon);
	
	const UInputAction* AimWeaponAction = PlayerInputData->AimWeaponAction;
	check(AimWeaponAction);
	PlayerEnhancedInput->BindAction(
		AimWeaponAction, ETriggerEvent::Started,
		this, &ThisClass::Input_AimWeaponPressed);
	
	PlayerEnhancedInput->BindAction(
		AimWeaponAction, ETriggerEvent::Completed,
		this, &ThisClass::Input_AimWeaponReleased);
	
	const UInputAction* FireWeaponAction = PlayerInputData->FireWeaponAction;
	check(FireWeaponAction);
	PlayerEnhancedInput->BindAction(
		FireWeaponAction, ETriggerEvent::Started,
		this, &ThisClass::Input_FireWeaponPressed);
	
	PlayerEnhancedInput->BindAction(
		FireWeaponAction, ETriggerEvent::Completed,
		this, &ThisClass::Input_FireWeaponReleased);
	
	const UInputAction* ReloadWeaponAction = PlayerInputData->ReloadWeaponAction;
	check(ReloadWeaponAction);
	PlayerEnhancedInput->BindAction(
		ReloadWeaponAction, ETriggerEvent::Started,
		this, &ThisClass::Input_ReloadWeapon);
}

void AFPSPlayerCharacter::Input_CycleWeapon()
{
	PlayerCombat->Initiate_CycleWeapon();
}

void AFPSPlayerCharacter::Input_AimWeaponPressed()
{
	PlayerCombat->Initiate_AimWeaponPressed();
}

void AFPSPlayerCharacter::Input_AimWeaponReleased()
{
	PlayerCombat->Initiate_AimWeaponReleased();
}

void AFPSPlayerCharacter::Input_FireWeaponPressed()
{
	PlayerCombat->Initiate_FireWeaponPressed();
}

void AFPSPlayerCharacter::Input_FireWeaponReleased()
{
	PlayerCombat->Initiate_FireWeaponReleased();
}

void AFPSPlayerCharacter::Input_ReloadWeapon()
{
	PlayerCombat->Initiate_ReloadWeapon();
}
