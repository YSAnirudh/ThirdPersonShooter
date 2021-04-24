// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EndGameController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AEndGameController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;
	UUserWidget* HUDDisplay;
	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f;

private:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	
};
