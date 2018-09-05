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
	FString Nom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantite;

	FItem()
	{
		//mettre l'initialisation des variables ici 
		ID = -1;
		Nom = "UNKNOWN";
		Quantite = 1;
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
