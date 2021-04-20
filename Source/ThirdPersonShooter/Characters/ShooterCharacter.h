// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AActorGun;
UCLASS()
class THIRDPERSONSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
private:
	void Shoot();
	void BoneManip();
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Walk();
	void UnWalk();
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	float PlayerSpeedForward = 600.f;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	float PlayerSpeedRight = 300.f;
	UPROPERTY(EditAnywhere)
	float AimSensitivity = 100.f;
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	float Health;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActorGun> GunClass;
	UPROPERTY()
	AActorGun* Gun;
};
