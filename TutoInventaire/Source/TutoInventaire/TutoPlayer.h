// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
/* insert include here */
#include "TutoDataBase.h"
#include "Engine.h"
#include "TutoItem.h"
#include "Data.h"
/* insert include here */
#include "TutoPlayer.generated.h"

UCLASS()
class TUTOINVENTAIRE_API ATutoPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutoPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TArray<FItem> Inventory;

	int32 NumberMaxItem = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool InventoryScreen = false;

	//The item to pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		AActor* ItemToPickUp;

	//Array of crafting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TArray<FCraft> Craft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int32 indexCraft;

	// Return the Number of Item From a specific ID
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		int32 GetNumberFromID(int32 TheID);

	// Return the Index of Item From a specific ID
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		int32 GetItemIndexWithID(int32 TheID);

	// Add an Item in the inventory with the specific ID
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void AddItemWithID(int32 TheID);

	// Remove an Item in the inventory with the specific ID
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void RemoveItemWithID(int32 TheID);

	UFUNCTION()
		void AddObject();

	UFUNCTION()
		void RemoveObject();

	UFUNCTION()
		void ChangeInventoryState();

	// Move the player forward and backward
	UFUNCTION(BlueprintCallable, Category = "Move")
		void MoveForward(float value);

	// Move the player right and left
	UFUNCTION(BlueprintCallable, Category = "Move")
		void MoveRight(float value);

	//handles use
	UFUNCTION()
		void OnUse();

	// Go UP in the crafting list
	UFUNCTION()
		void UpCraft();

	// GO DOWN in the crafting list
	UFUNCTION()
		void DownCraft();

	// Check if we have all items to craft the selected item
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		bool GetEnoughItem(int32 index);

	//Remove an item in the inventory with the specific ID and Number
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void RemoveItemWithIDAndNumber(int32 TheID, int32 TheNumber);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void CraftItem(int32 index);

	
};
