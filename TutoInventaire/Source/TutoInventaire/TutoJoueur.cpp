// Fill out your copyright notice in the Description page of Project Settings.

#include "TutoJoueur.h"

// Sets default values
ATutoJoueur::ATutoJoueur()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATutoJoueur::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATutoJoueur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATutoJoueur::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Return the Number of Item from a specific ID
int32 ATutoJoueur::GetNumberFromID(int32 TheID)
{
	int32 retour = -1;
	for (int32 index = 0; index < Inventaire.Num(); index++)
	{
		if (Inventaire[index].ID == TheID)
		{
			retour = Inventaire[index].Quantite;
			break;
		}
	}
	return retour;
}
	for (int32 index = 0; index < Inventaire.Num(); index++)
	{
		if (Inventaire[index].ID == TheID)
		{
			retour = index;
			break;
		}
	}
	return retour;
