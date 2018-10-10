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

	// use our custom HUD class
	//HUDClass = AUnrealCPPHUD::StaticClass();
}

void ATutoGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartMatch();

	SetCurrentState(EGamePlayState::EPlaying);

	MyCharacter = Cast<ATutoPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATutoGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetWorld()->GetMapName();

	if (MyCharacter)
	{
		if (FMath::IsNearlyZero(MyCharacter->GetHealth(), 0.001f))
		{
			SetCurrentState(EGamePlayState::EGameOver);
		}
	}
}

EGamePlayState ATutoGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ATutoGameMode::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void ATutoGameMode::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
	{
		// do nothing
	}
	break;
	// Unknown/default state
	case EGamePlayState::EGameOver:
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
	break;
	// Unknown/default state
	default:
	case EGamePlayState::EUnknown:
	{
		// do nothing
	}
	break;
	}
}

