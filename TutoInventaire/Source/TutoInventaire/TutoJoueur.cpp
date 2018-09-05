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

	InputComponent->BindAction("AjoutObjet", IE_Pressed, this, &ATutoJoueur::AjoutObjet);
	InputComponent->BindAction("SuppressionObjet", IE_Pressed, this, &ATutoJoueur::SuppressionObjet);

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
}/* Return the Index of Item from a specific ID */int32 ATutoJoueur::GetItemIndexWithID(int32 TheID){	int32 retour = -1;
	for (int32 index = 0; index < Inventaire.Num(); index++)
	{
		if (Inventaire[index].ID == TheID)
		{
			retour = index;
			break;
		}
	}
	return retour;}/* Add an Item in the inventory with the specific ID */void ATutoJoueur::AddItemWithID(int32 TheID){	int32 Number = GetNumberFromID(TheID);	if (Number < NombreMaxItem)	{		int32 index = GetItemIndexWithID(TheID);		Inventaire[index].Quantite++;	}	else	{		if (GEngine)		{			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't ADD Item with ID : " + FString::FromInt(TheID)));		}	}}/* Remove an Item in the inventory with the specific ID */void ATutoJoueur::RemoveItemWithID(int32 TheID){	int32 Number = GetNumberFromID(TheID);	if (Number > 0)	{		int32 index = GetItemIndexWithID(TheID);		Inventaire[index].Quantite--;	}	else	{		if (GEngine)		{			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't REMOVE Item with ID : " + FString::FromInt(TheID)));		}	}}void ATutoJoueur::AjoutObjet(){	AddItemWithID(0);}void ATutoJoueur::SuppressionObjet(){	RemoveItemWithID(0);}

