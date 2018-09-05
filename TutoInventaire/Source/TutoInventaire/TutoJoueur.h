// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
/* insert include here */
#include "TutoDataBase.h"
#include "Engine.h"
/* insert include here */
#include "TutoJoueur.generated.h"

UCLASS()
class TUTOINVENTAIRE_API ATutoJoueur : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutoJoueur();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TArray<FItem> Inventaire;

	const int32 NombreMaxItem = 5;

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
	
};
