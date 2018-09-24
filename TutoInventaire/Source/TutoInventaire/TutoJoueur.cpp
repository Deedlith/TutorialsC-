// Fill out your copyright notice in the Description page of Project Settings.

#include "TutoJoueur.h"

// Sets default values
ATutoJoueur::ATutoJoueur()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NumberMaxItem = 5;

	FCraft CurrentCraft;
	FRequirement CurrentRequirement;

	// Kit Soin
	CurrentCraft.ID = 0;
	CurrentCraft.Quantity = 0;
	CurrentCraft.Name = "Kit Soin";
	CurrentRequirement.ID = 0;
	CurrentRequirement.Quantity = 1;
	CurrentCraft.Requirement.Add(CurrentRequirement);
	CurrentRequirement.ID = 2;
	CurrentRequirement.Quantity = 1;
	CurrentCraft.Requirement.Add(CurrentRequirement);

	Craft.Add(CurrentCraft);

	CurrentCraft.Requirement.Empty();

	// Knife
	CurrentCraft.ID = 1;
	CurrentCraft.Quantity = 0;
	CurrentCraft.Name = "Knife";
	CurrentRequirement.ID = 4;
	CurrentRequirement.Quantity = 1;
	CurrentCraft.Requirement.Add(CurrentRequirement);
	CurrentRequirement.ID = 5;
	CurrentRequirement.Quantity = 1;
	CurrentCraft.Requirement.Add(CurrentRequirement);
	CurrentRequirement.ID = 1;
	CurrentRequirement.Quantity = 1;
	CurrentCraft.Requirement.Add(CurrentRequirement);

	Craft.Add(CurrentCraft);

	CurrentCraft.Requirement.Empty();

	// Crochetage
	CurrentCraft.ID = 2;
	CurrentCraft.Quantity = 0;
	CurrentCraft.Name = "Crochetage";
	CurrentRequirement.ID = 1;
	CurrentRequirement.Quantity = 2;
	CurrentCraft.Requirement.Add(CurrentRequirement);

	Craft.Add(CurrentCraft);

	CurrentCraft.Requirement.Empty();

	// Molotov
	CurrentCraft.ID = 3;
	CurrentCraft.Quantity = 0;
	CurrentCraft.Name = "Molotov";
	CurrentRequirement.ID = 2;
	CurrentRequirement.Quantity = 1;
	CurrentCraft.Requirement.Add(CurrentRequirement);
	CurrentRequirement.ID = 3;
	CurrentRequirement.Quantity = 1;
	CurrentCraft.Requirement.Add(CurrentRequirement);

	Craft.Add(CurrentCraft);

	CurrentCraft.Requirement.Empty();

	// Bandage
	CurrentCraft.ID = 4;
	CurrentCraft.Quantity = 0;
	CurrentCraft.Name = "Bandage";
	CurrentRequirement.ID = 3;
	CurrentRequirement.Quantity = 2;
	CurrentCraft.Requirement.Add(CurrentRequirement);

	Craft.Add(CurrentCraft);

	CurrentCraft.Requirement.Empty();

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

	InputComponent->BindAction("AddObject", IE_Pressed, this, &ATutoJoueur::AddObject);
	InputComponent->BindAction("RemoveObject", IE_Pressed, this, &ATutoJoueur::RemoveObject);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ATutoJoueur::ChangeInventoryState);
	InputComponent->BindAction("Action", IE_Pressed, this, &ATutoJoueur::OnUse);
	InputComponent->BindAction("UpCraft", IE_Pressed, this, &ATutoJoueur::UpCraft);
	InputComponent->BindAction("DownCraft", IE_Pressed, this, &ATutoJoueur::DownCraft);

	InputComponent->BindAxis("Forward", this, &ATutoJoueur::MoveForward);
	InputComponent->BindAxis("Right", this, &ATutoJoueur::MoveRight);
	InputComponent->BindAxis("TurnAtRate", this, &ATutoJoueur::AddControllerYawInput);
	InputComponent->BindAxis("LookUpAtRate", this, &ATutoJoueur::AddControllerPitchInput);
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
/* Return the Index of Item from a specific ID */
int32 ATutoJoueur::GetItemIndexWithID(int32 TheID)
{
	int32 retour = -1;
	for (int32 index = 0; index < Inventaire.Num(); index++)
	{
		if (Inventaire[index].ID == TheID)
		{
			retour = index;
			break;
		}
	}
	return retour;
}

/* Add an Item in the inventory with the specific ID */
void ATutoJoueur::AddItemWithID(int32 TheID)
{
	int32 Number = GetNumberFromID(TheID);
	if (Number < NumberMaxItem)
	{
		int32 index = GetItemIndexWithID(TheID);
		Inventaire[index].Quantite++;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't ADD Item with ID : " + FString::FromInt(TheID)));
		}
	}
}

/* Remove an Item in the inventory with the specific ID */
void ATutoJoueur::RemoveItemWithID(int32 TheID)
{
	int32 Number = GetNumberFromID(TheID);
	if (Number > 0)
	{
		int32 index = GetItemIndexWithID(TheID);
		Inventaire[index].Quantite--;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't REMOVE Item with ID : " + FString::FromInt(TheID)));
		}
	}
}

void ATutoJoueur::AddObject()
{
	AddItemWithID(3);
	AddItemWithID(3);
}

void ATutoJoueur::RemoveObject()
{
	RemoveItemWithID(0);
}

void ATutoJoueur::ChangeInventoryState()
{
	InventaireVisuel = !InventaireVisuel;
}

// Move the player forward and backward
void ATutoJoueur::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		if (!InventaireVisuel)
		{
			//Find out which way is forward
			FRotator Rotation = Controller->GetControlRotation();
			//limit pitch when walking or falling
			if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
			{
				Rotation.Pitch = 0.0f;
			}
			//Add Movement in that direction
			const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
			AddMovementInput(Direction, value);
		}
	}
}

// Move the player right and left
void ATutoJoueur::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		if (!InventaireVisuel)
		{
			//Find out which way is forward
			FRotator Rotation = Controller->GetControlRotation();

			//Add Movement in that direction
			const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
			AddMovementInput(Direction, value);
		}
	}
}

void ATutoJoueur::OnUse()
{
	if (InventaireVisuel)
	{
		bool nbItems = GetEnoughItem(indexCraft);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, nbItems ? TEXT("true") : TEXT("false"));
		}
		if (nbItems)
			CraftItem(indexCraft);
	}
	else
	{
		if (ItemToPickUp)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Picked Up !"));
			}

			//Cast Item
			ATutoItem* CurrentItem = Cast<ATutoItem>(ItemToPickUp);
			if (CurrentItem)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Infos Received, ID :" + FString::FromInt(CurrentItem->info.ID)));
				}

				//Get Index of Item Pick UP
				int32 index = GetItemIndexWithID(CurrentItem->info.ID);

				//Item doesn't exit add them to the Inventaire
				if (index == -1)
				{
					FItem NewItem = CurrentItem->info;
					int32 TheIndex = Inventaire.Add(NewItem);
				}
				//Item already exist, update the quantity
				else
				{
					AddItemWithID(CurrentItem->info.ID);
				}
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fail to retreive infos"));
				}
			}
			ItemToPickUp->Destroy();
			ItemToPickUp = nullptr;
		}
	}
}

void ATutoJoueur::UpCraft()
{
	if (InventaireVisuel && indexCraft - 1 >= 0)
	{
		indexCraft--;
	}
}

void ATutoJoueur::DownCraft()
{
	if (InventaireVisuel && indexCraft + 1 < Craft.Num())
	{
		indexCraft++;
	}
}

bool ATutoJoueur::GetEnoughItem(int32 index)
{
	bool canCraft = true;

	FCraft CurrentCraft = Craft[index];
	for (int i = 0; i < CurrentCraft.Requirement.Num(); i++)
	{
		int32 NBItems = GetNumberFromID(CurrentCraft.Requirement[i].ID);
		if (NBItems < CurrentCraft.Requirement[i].Quantity)
		{
			canCraft = false;
			return canCraft;
		}
	}
	return canCraft;
}

void ATutoJoueur::RemoveItemWithIDAndNumber(int32 TheID, int32 TheNumber) 
{
	int32 Number = GetNumberFromID(TheID);
	if (Number - TheNumber > 0)
	{
		int32 index = GetItemIndexWithID(TheID);
		Inventaire[index].Quantite -= TheNumber;
	}
	else
	{
		int32 index = GetItemIndexWithID(TheID);
		Inventaire[index].Quantite = 0;
	}
}

void ATutoJoueur::CraftItem(int32 index)
{
	Craft[index].Quantity++;
	for (int32 i = 0; i < Craft[index].Requirement.Num(); i++)
	{
		RemoveItemWithIDAndNumber(Craft[index].Requirement[i].ID, Craft[index].Requirement[i].Quantity);
	}
}


