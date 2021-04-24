// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerShooter.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AAIControllerShooter : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	bool IsDead() const;
protected:
	virtual void BeginPlay() override;
private:
	class APawn* PlayerPawn = NULL;
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* EnemyAIBehavior;

};
