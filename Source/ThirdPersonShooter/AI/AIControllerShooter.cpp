// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerShooter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../Characters/ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
void AAIControllerShooter::BeginPlay() 
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (EnemyAIBehavior != nullptr) {
        RunBehaviorTree(EnemyAIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AAIControllerShooter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

bool AAIControllerShooter::IsDead() const
{
    AShooterCharacter* Enemy = Cast<AShooterCharacter>(GetPawn());
    if (Enemy != nullptr) {
        return Enemy->IsDead();
    }
    return false;
}
