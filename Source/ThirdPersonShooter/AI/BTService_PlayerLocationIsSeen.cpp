// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIsSeen.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIsSeen::UBTService_PlayerLocationIsSeen() 
{
    NodeName = TEXT("Player Location If Seen");
}

void UBTService_PlayerLocationIsSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    AAIController* OwnerController = OwnerComp.GetAIOwner();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(this,0);
    if (!PlayerPawn) return;
    if (!OwnerController) return;
    if (OwnerController->LineOfSightTo(PlayerPawn)) {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    } else {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
