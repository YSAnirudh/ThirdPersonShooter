// Copyright Epic Games, Inc. All Rights Reserved.


#include "ThirdPersonShooterGameModeBase.h"
#include "GameFramework/PlayerController.h"

void AThirdPersonShooterGameModeBase::PawnKilled(APawn* PawnKilled) 
{
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    
}
