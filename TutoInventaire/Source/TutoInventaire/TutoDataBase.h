// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutoDataBase.generated.h"


USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

		//mettre vos variables et fonctions ici

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	FItem()
	{
		//mettre l'initialisation des variables ici 
		ID = -1;
		Name = "UNKNOWN";
		Quantity = 0;
	}

};

USTRUCT(BlueprintType)
struct FRequirement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirement")
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirement")
	int32 Quantity;

	FRequirement()
	{
		ID = -1;
		Quantity = 1;
	}
};

USTRUCT(BlueprintType)
struct FCraft
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		TArray<FRequirement> Requirement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		FString Name;

	FCraft()
	{
		ID = -1;
		Quantity = 1;
		Name = "UNKNOWN";
	}
};

USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float fireRate; //time between fire (plus il est bas plus on tire vite)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int bulletPerMagazine; //Nb balles max par chargeur
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int currentBullet; // nb bullet in magazine (current)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int totalBullet; // nb bullet on me
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int damage; // damage of weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float weaponRange; // range for fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float reloadTime; // time of reloading

	FWeapon(bool init = false)
	{
		if (init)
		{
			name = "";
			fireRate = FMath::RandRange(0.1f, 1.0f);
			bulletPerMagazine = FMath::RandRange(10, 20);
			currentBullet = bulletPerMagazine;
			totalBullet = FMath::RandRange(50, 200);
			damage = FMath::RandRange(10, 100);
			weaponRange = FMath::RandRange(100.0f, 500.0f);
			reloadTime = FMath::RandRange(1.0f, 3.0f);
		}
		else
		{
			name = "";
			fireRate = 1.0f;
			bulletPerMagazine = 10;
			currentBullet = bulletPerMagazine;
			totalBullet = 10;
			damage = 10;
			weaponRange = 200.0f;
			reloadTime = 2.0f;
		}
	}
};

UCLASS()
class TUTOINVENTAIRE_API ATutoDataBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutoDataBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
