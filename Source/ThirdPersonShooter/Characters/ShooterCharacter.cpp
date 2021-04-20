// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Actors/ActorGun.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActor<AActorGun>(GunClass);
	BoneManip();
	Gun->SetOwner(this);
	Health = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Walk"), IE_Pressed ,this, &AShooterCharacter::Walk);
	PlayerInputComponent->BindAction(TEXT("Walk"), IE_Released ,this, &AShooterCharacter::UnWalk);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) 
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Health > 0 && DamageCauser) {
		Health -= DamageAmount;
	}

	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);

	if (Health <= 0) {
		Health = 0.f;
		// ActorDied
		return DamageAmount;
	}
	return DamageAmount;
}

void AShooterCharacter::Shoot() 
{
	Gun->Shoot();
}

void AShooterCharacter::BoneManip() 
{
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
}

void AShooterCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
	// FVector MoveForward = GetActorLocation() + GetActorForwardVector()*AxisValue*PlayerSpeedForward*GetWorld()->GetDeltaSeconds();
	// SetActorLocation(MoveForward);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
	// FVector MoveRight = GetActorLocation() + GetActorRightVector()*AxisValue*PlayerSpeedRight*GetWorld()->GetDeltaSeconds();
	// SetActorLocation(MoveRight);
}

void AShooterCharacter::Walk() 
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed*2/7;
}

void AShooterCharacter::UnWalk() 
{
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed*7/2;
}

void AShooterCharacter::LookUp(float AxisValue) 
{
	FRotator LookUp = GetActorRotation() + FRotator(AxisValue * AimSensitivity * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f);
	SetActorRotation(LookUp);
}

void AShooterCharacter::LookRight(float AxisValue) 
{
	FRotator LookRight = GetActorRotation() + FRotator(0.0f, AxisValue * AimSensitivity * GetWorld()->GetDeltaSeconds(), 0.0f);
	SetActorRotation(LookRight);
}

