// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutoDataBase.generated.h"

UENUM(BlueprintType)
enum class ETypeWeapon : uint8
{
	ShotGun,
	Pistol,
	Sniper,
	Rifle
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		TArray<FRequirement> Requirement;

	FItem()
	{
		//mettre l'initialisation des variables ici 
		ID = -1;
		Name = "UNKNOWN";
		Quantity = 0;
	}

};

USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "time between fire (plus il est bas plus on tire vite - [0.1f, 1.0f]"))
	float fireRate; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "Nb balles max par chargeur - [3f, 60f]"))
	int bulletPerMagazine; 
	int currentBullet; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "damage of weapon - [10f, 100f]"))
	int damage; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "range for fire - [100f, 500f]"))
	float weaponRange; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "time of reloading - [1.0f, 3.0f]"))
	float reloadTime; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ToolTip = "type of weapon (SHOTGUN , PISTOL, SNIPER, RIFLE)"))
	ETypeWeapon typeWeapon;

	FWeapon()
	{
		name = "";
		typeWeapon = ETypeWeapon::Pistol;
		fireRate = 1.0f;
		bulletPerMagazine = 10;
		currentBullet = bulletPerMagazine;
		damage = 10;
		weaponRange = 200.0f;
		reloadTime = 2.0f;
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
