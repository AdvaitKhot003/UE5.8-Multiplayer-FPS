// No Copyright.

#include "Character/FPSPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
}

void AFPSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AFPSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
