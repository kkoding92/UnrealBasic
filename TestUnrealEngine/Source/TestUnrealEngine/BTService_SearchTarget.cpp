// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.0f; // TickNode 주기
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return;

	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation(); //위치
	float SearchRadius = 500.f;

	if (World == nullptr)
		return;

	//충돌 결과를 담을 곳
	TArray<FOverlapResult> OverlapResults; 
	//몬스터가 자기 자신은 찾지 않도록 하는 버전
	FCollisionQueryParams QuertParams(NAME_None, false, CurrentPawn); 

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults, 
		Center, 
		FQuat::Identity, 
		ECollisionChannel::ECC_EngineTraceChannel2, 
		FCollisionShape::MakeSphere(SearchRadius),
		QuertParams);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			AMyCharacter* MyCharacter = Cast<AMyCharacter>(OverlapResult.GetActor());
			if (MyCharacter && MyCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), MyCharacter);

				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
	}

	DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
}