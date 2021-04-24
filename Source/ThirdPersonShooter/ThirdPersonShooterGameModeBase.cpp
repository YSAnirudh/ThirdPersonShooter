// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThirdPersonShooterGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "./AI/AIControllerShooter.h"
#include "EngineUtils.h"
void AThirdPersonShooterGameModeBase::PawnKilled(APawn* PawnKilled) 
{
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    
    if (PlayerController != nullptr) {
        EndGame(false);
        return;
    }
    for (AAIControllerShooter* Controller : TActorRange<AAIControllerShooter>(GetWorld())) {
        if (!Controller->IsDead()) return;
    }
    EndGame(true);
}

void AThirdPersonShooterGameModeBase::EndGame(bool PlayerWon) 
{
    for (AController* Controller : TActorRange<AController>(GetWorld())) {
        Controller->GameHasEnded(Controller->GetPawn(), !(PlayerWon ^ Controller->IsPlayerController()));
    }
}
