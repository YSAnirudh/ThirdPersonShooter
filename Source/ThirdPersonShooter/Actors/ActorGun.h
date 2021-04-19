// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorGun.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API AActorGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Shoot();
private:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere)
	float ShootRange = 2000.f;

	AController* OwnerController;



};
