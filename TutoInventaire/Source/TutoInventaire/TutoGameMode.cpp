// Fill out your copyright notice in the Description page of Project Settings.

#include "TutoGameMode.h"


ATutoGameMode::ATutoGameMode(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn>
		PlayerPawnObject(TEXT("Pawn'/Game/AddingContent/Blueprint/BP_TutoPlayer.BP_TutoPlayer_C'"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

void ATutoGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HELLO WORLD"));
	}
}

