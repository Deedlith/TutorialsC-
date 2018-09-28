// Fill out your copyright notice in the Description page of Project Settings.

#include "TutoPlayer.h"


// Sets default values
ATutoPlayer::ATutoPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATutoPlayer::InitCraft()
{
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

ATutoPlayer::ATutoPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitCraft();
	//ATutoPlayer();
	//no weapon at beginning
	currentWeapon = nullptr;
	//player doesn't shoot at beginning
	isFiring = false;

	//create player's camera
	camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	//Attach to player
	camera->SetupAttachment(GetCapsuleComponent());

	GetMesh()->SetupAttachment(camera);
}
// Called when the game starts or when spawned
void ATutoPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATutoPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATutoPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("AddObject", IE_Pressed, this, &ATutoPlayer::AddObject);
	InputComponent->BindAction("RemoveObject", IE_Pressed, this, &ATutoPlayer::RemoveObject);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ATutoPlayer::ChangeInventoryState);
	InputComponent->BindAction("Action", IE_Pressed, this, &ATutoPlayer::OnUse);
	InputComponent->BindAction("UpCraft", IE_Pressed, this, &ATutoPlayer::UpCraft);
	InputComponent->BindAction("DownCraft", IE_Pressed, this, &ATutoPlayer::DownCraft);
	InputComponent->BindAction("LeftItemInventory", IE_Pressed, this, &ATutoPlayer::LeftItemInventory);
	InputComponent->BindAction("RightItemInventory", IE_Pressed, this, &ATutoPlayer::RightItemInventory);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATutoPlayer::Fire);
	InputComponent->BindAction("Fire", IE_Released, this, &ATutoPlayer::StopFire);
	InputComponent->BindAction("Reload", IE_Pressed, this, &ATutoPlayer::Reload);
	//InputComponent->BindAction("Action", IE_Pressed, this, &ATutoPlayer::Action); NEED TO MERGE

	InputComponent->BindAxis("Forward", this, &ATutoPlayer::MoveForward);
	InputComponent->BindAxis("Right", this, &ATutoPlayer::MoveRight);
	InputComponent->BindAxis("TurnAtRate", this, &ATutoPlayer::AddControllerYawInput);
	InputComponent->BindAxis("LookUpAtRate", this, &ATutoPlayer::AddControllerPitchInput);
}

// Return the Number of Item from a specific ID
int32 ATutoPlayer::GetNumberFromID(int32 TheID)
{
	int32 retour = -1;
	for (int32 index = 0; index < Inventory.Num(); index++)
	{
		if (Inventory[index].ID == TheID)
		{
			retour = Inventory[index].Quantity;
			break;
		}
	}
	return retour;
}
/* Return the Index of Item from a specific ID */
int32 ATutoPlayer::GetItemIndexWithID(int32 TheID)
{
	int32 retour = -1;
	for (int32 index = 0; index < Inventory.Num(); index++)
	{
		if (Inventory[index].ID == TheID)
		{
			retour = index;
			break;
		}
	}
	return retour;
}

/* Add an Item in the inventory with the specific ID */
void ATutoPlayer::AddItemWithID(int32 TheID)
{
	int32 Number = GetNumberFromID(TheID);
	if (Number < NumberMaxItem)
	{
		int32 index = GetItemIndexWithID(TheID);
		Inventory[index].Quantity++;
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
void ATutoPlayer::RemoveItemWithID(int32 TheID)
{
	int32 Number = GetNumberFromID(TheID);
	if (Number > 0)
	{
		int32 index = GetItemIndexWithID(TheID);
		Inventory[index].Quantity--;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't REMOVE Item with ID : " + FString::FromInt(TheID)));
		}
	}
}

void ATutoPlayer::AddObject()
{
	AddItemWithID(3);
	AddItemWithID(3);
}

void ATutoPlayer::RemoveObject()
{
	RemoveItemWithID(0);
}

void ATutoPlayer::ChangeInventoryState()
{
	InventoryScreen = !InventoryScreen;
}

// Move the player forward and backward
void ATutoPlayer::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		if (!InventoryScreen)
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
void ATutoPlayer::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		if (!InventoryScreen)
		{
			//Find out which way is forward
			FRotator Rotation = Controller->GetControlRotation();

			//Add Movement in that direction
			const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
			AddMovementInput(Direction, value);
		}
	}
}

//Move mouse vertical
/**
 |89| valeur max sinon camera peut s'inverser et avoir la tête à l'envers
**/
void ATutoPlayer::LookUp(float value)
{
	//reverse mouse's roatation to up, (View up)
	float tmpAmount = value * -1;
	if (value != 0)
	{
		//if go down
		if (tmpAmount < 0 && camera->RelativeRotation.Pitch + tmpAmount > -89)
		{
			camera->AddRelativeRotation(FRotator(tmpAmount, 0, 0));
		}
		//if go up
		else if (tmpAmount > 0 && camera->RelativeRotation.Pitch + tmpAmount < 89)
		{
			camera->AddRelativeRotation(FRotator(tmpAmount, 0, 0));
		}
	}
}

void ATutoPlayer::OnUse()
{
	if (InventoryScreen)
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
					int32 TheIndex = Inventory.Add(NewItem);
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

void ATutoPlayer::UpCraft()
{
	if (InventoryScreen && indexCraft - 1 >= 0)
	{
		indexCraft--;
	}
}

void ATutoPlayer::DownCraft()
{
	if (InventoryScreen && indexCraft + 1 < Craft.Num())
	{
		indexCraft++;
	}
}

void ATutoPlayer::LeftItemInventory()
{
	if (InventoryScreen && indexItemsInventory - 1 >= 0)
	{
		indexItemsInventory--;
	}
}

bool ATutoPlayer::GetColorSelected(int32 index)
{
	if (index == indexItemsInventory)
		return true;
	return false;
}

void ATutoPlayer::RightItemInventory()
{
	if (InventoryScreen)
	{
		indexItemsInventory++;
	}
}

bool ATutoPlayer::GetEnoughItem(int32 index)
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


void ATutoPlayer::RemoveItemWithIDAndNumber(int32 TheID, int32 TheNumber)
{
	int32 Number = GetNumberFromID(TheID);
	if (Number - TheNumber > 0)
	{
		int32 index = GetItemIndexWithID(TheID);
		Inventory[index].Quantity -= TheNumber;
	}
	else
	{
		int32 index = GetItemIndexWithID(TheID);
		Inventory[index].Quantity = 0;
	}
}

void ATutoPlayer::CraftItem(int32 index)
{
	Craft[index].Quantity++;
	for (int32 i = 0; i < Craft[index].Requirement.Num(); i++)
	{
		RemoveItemWithIDAndNumber(Craft[index].Requirement[i].ID, Craft[index].Requirement[i].Quantity);
	}
}

//Handle fire
void ATutoPlayer::Fire()
{
	isFiring = true;
}
void ATutoPlayer::StopFire()
{
	isFiring = false;
}


void ATutoPlayer::Reload()
{
	//if (currentWeapon)
	//	currentWeapon->Reload();
}

//Get weapon
void ATutoPlayer::Action()
{
	//options for raycast
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Init
	FHitResult RV_Hit(ForceInit);

	//Get camera's position
	FVector startFire = camera->GetComponentLocation();
	//create a point from 500 m (player) in the camera's direction
	FVector endFire = startFire + (camera->GetComponentRotation().Vector() * 500.0f);

	//call GetWorld() from within an actor extending class	GetWorld()->LineTraceSingleByChannel
	(
		RV_Hit,					//result
		startFire,				//start
		endFire,				//end
		ECC_Visibility,			//collision channel
		RV_TraceParams
	);

	//Collision !!!!
	if (RV_Hit.GetActor())
	{
		ATutoWeapon* weapon = Cast<ATutoWeapon>(RV_Hit.GetActor());
		if (weapon)
		{
			Equip(weapon);
		}
	}
}

void ATutoPlayer::Equip(ATutoWeapon* aWeapon)
{
	//if we already have a weapon in hand
	if (currentWeapon)
	{
		//Detach
		currentWeapon->DetachRootComponentFromParent();
		currentWeapon->SetOwner(nullptr);
	}
	currentWeapon = aWeapon;
	currentWeapon->SetOwner(this);
	currentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("GripPoint"));
	currentWeapon->SetActorRelativeRotation(FRotator(0, 90.0f, 0));
}

