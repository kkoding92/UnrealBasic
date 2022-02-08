// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Super : 부모 UAnimInstance, 언리얼 문법
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 소유주가져오기, Try-없을 수도 있음.
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		//Velocity의 크기
		Speed = Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}

