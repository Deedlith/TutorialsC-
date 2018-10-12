// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
/* insert include here */
#include "TutoDataBase.h"
#include "Engine.h"
#include "TutoItem.h"
#include "Data.h"
#include "TutoWeapon.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
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
		TArray<FItem> Craft;

	//Array of weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TArray<FWeapon> InventoryWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int32 indexCraft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		int32 indexItemsInventory;

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

	UFUNCTION()
		void InitCraft();

	// Move the player forward and backward
	UFUNCTION(BlueprintCallable, Category = "Move")
		void MoveForward(float value);

	// Move the player right and left
	UFUNCTION(BlueprintCallable, Category = "Move")
		void MoveRight(float value);

	//Move mouse vertical
	void LookUp(float value);

	//handles use
	UFUNCTION()
		void OnUse();

	// Go UP in the crafting list
	UFUNCTION()
		void UpCraft();

	// GO DOWN in the crafting list
	UFUNCTION()
		void DownCraft();

	// Go LEFT int the inventory list
	UFUNCTION()
		void LeftItemInventory();

	// GO RIGHT int the inventory list
	UFUNCTION()
		void RightItemInventory();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		bool GetColorSelected(int32 index);

	// Check if we have all items to craft the selected item
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		bool GetEnoughItem(int32 index);

	//Remove an item in the inventory with the specific ID and Number
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void RemoveItemWithIDAndNumber(int32 TheID, int32 TheNumber);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void CraftItem(int32 index);

#pragma region WEAPON  
	//Handle fire
	void Fire();
	void StopFire();

	//Is player firing ?
	bool isFiring;

	bool canTakeWeapon = false;

	ATutoWeapon* WeaponToPickUp;
	void Reload();

	void Equip(ATutoWeapon* aWeapon);

	const int32 MAXBULLETRIFLE = 60;
	const int32 MAXBULLETPISTOL = 12;
	const int32 MAXBULLETSHOTGUN = 8;
	const int32 MAXBULLETSNIPER = 3;
	TMap<ETypeWeapon, int32> nbBulletsPerType;

	//Weapon
	UPROPERTY(EditDefaultsOnly, BLueprintReadWrite, Category = "Weapon")
		ATutoWeapon* currentWeapon;

	//composants
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* camera;

	/* Return the Index of WeaponItem from a specific type */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		int32 GetItemWeaponIndexWithType(ETypeWeapon typeW);

	bool DoTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams);

	ATutoWeapon* weaponRaycast;

	FString GetEnumAsString(ETypeWeapon EnumValue);
#pragma endregion WEAPON  

#pragma region HEALTH  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float PreviousHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float redFlash;

	FTimeline MyTimeline;
	float CurveFloatValue;
	float TimelineValue;
	FTimerHandle MemberTimerHandle;

	/** Get Health */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	/** Update Health */
	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange);

	/** Get Health Text */
	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	/** Damage Timer */
	UFUNCTION()
		void DamageTimer();

	/** Set Damage State */
	UFUNCTION()
		void SetDamageState();


	/** Play Flash */
	UFUNCTION(BlueprintPure, Category = "Health")
		bool PlayFlash();

	//UFUNCTION()
	//	void ReceivePointDamage(float Damage, const UDamageType * DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo);
#pragma endregion HEALTH  
};
