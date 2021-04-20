// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
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
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	FHitResult BulletHit;
	FVector InHitRotation;
	bool bHit = GetHitLineOfSight(BulletHit, InHitRotation);
	if (bHit) {
		AActor* ActorThatIsHit = BulletHit.GetActor();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, BulletHit.Location, InHitRotation.Rotation());
		FPointDamageEvent DamageEvent(BulletDamage, BulletHit, InHitRotation, NULL);
		ActorThatIsHit->TakeDamage(BulletDamage, DamageEvent, OwnerController, this);
	}
	DrawDebugPoint(GetWorld(),BulletHit.Location , 10.f, FColor::Blue, true, 10.f);
	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 10.f, FColor::Red, true);
}

bool AActorGun::GetHitLineOfSight(FHitResult& BulletHit, FVector& InHitRotation) 
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return false;
	OwnerController = Cast<AController>(OwnerPawn->GetController());
	if (!OwnerController) return false;
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(OUT Location, OUT Rotation);
	InHitRotation = -Rotation.Vector();
	FVector HitEnd = Location + Rotation.Vector() * ShootRange;
	FCollisionQueryParams CollisionParams;
	return GetWorld()->LineTraceSingleByChannel(
		OUT BulletHit,
		Location,
		HitEnd,
		ECollisionChannel::ECC_GameTraceChannel1,
		CollisionParams
	);
}

