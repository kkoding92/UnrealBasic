// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

UMyStatComponent::UMyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	//InitializeComponent가 실행되려면 필요
	bWantsInitializeComponent = true;

	Level = 1;
}

void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}

void UMyStatComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(NewLevel);
		if (StatData)
		{
			Level = StatData->Level;
			Hp = StatData->MaxHP;
			Attack = StatData->Attack;
		}
	}
}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	Hp -= DamageAmount;
	if (Hp < 0)
		Hp = 0;

	UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);
}

