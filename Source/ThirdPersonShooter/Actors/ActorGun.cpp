// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#define OUT
// Sets default values
AActorGun::AActorGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AActorGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorGun::Shoot() 
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	OwnerController = Cast<AController>(OwnerPawn->GetController());
	if (!OwnerController) return;
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(OUT Location, OUT Rotation);

	FVector HitEnd = Location + Rotation.Vector() * ShootRange;
	FHitResult BulletHit;
	FCollisionQueryParams CollisionParams;
	GetWorld()->LineTraceSingleByChannel(
		OUT BulletHit,
		Location,
		HitEnd,
		ECollisionChannel::ECC_GameTraceChannel1,
		CollisionParams
	);
	FVector BulletHitLocation = BulletHit.Location;
	DrawDebugPoint(GetWorld(),BulletHitLocation , 10.f, FColor::Blue, true, 10.f);
	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 10.f, FColor::Red, true);
}

