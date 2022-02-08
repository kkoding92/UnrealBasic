// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Super : �θ� UAnimInstance, �𸮾� ����
	Super::NativeUpdateAnimation(DeltaSeconds);

	// �����ְ�������, Try-���� ���� ����.
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		//Velocity�� ũ��
		Speed = Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}

