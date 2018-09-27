// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutoWeapon.h"
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
struct FWeapons
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
	ATutoWeapon* Weapon;

	FWeapons()
	{
		Weapon = nullptr;
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
