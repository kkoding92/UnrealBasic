// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();

	//PAWN 객체 빙의 했을 때 안 했을 때
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
private:
	void RandomMove();

private:
	FTimerHandle TimerHandle;
};

