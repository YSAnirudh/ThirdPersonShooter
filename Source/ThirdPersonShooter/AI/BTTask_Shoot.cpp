// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Characters/ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr) {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* Enemy = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (!Enemy) {
        return EBTNodeResult::Failed;
    }

    Enemy->Shoot();
    return EBTNodeResult::Succeeded;
}
