// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameController.h"
#include "Blueprint/UserWidget.h"

void AEndGameController::BeginPlay() 
{
    Super::BeginPlay();

    HUDDisplay = CreateWidget(this, HUDClass);
    if (HUDDisplay != nullptr) {
        HUDDisplay->AddToViewport();
    }
}

void AEndGameController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    if (HUDDisplay != nullptr && HUDDisplay->IsInViewport()) {
        HUDDisplay->RemoveFromViewport();
    }
    if (bIsWinner) {
        UUserWidget* WinScreen = CreateWidget(this, WinClass);
        if(WinScreen != nullptr) {
            WinScreen->AddToViewport();
        }
    } else {
        UUserWidget* LoseScreen = CreateWidget(this, LoseClass);
        if(LoseScreen != nullptr) {
            LoseScreen->AddToViewport();
        }
    }

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}
