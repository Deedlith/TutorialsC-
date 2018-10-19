// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutoDataBase.h"
#include "Components/ArrowComponent.h"
#include "Bag.generated.h"

class ATutoItem;

UCLASS()
class TUTOINVENTAIRE_API ABag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	/** Change the collisions for every differents states */
	void DisableCollisions();
	void EnableCollisions();

	void AddItem(ATutoItem* theItem);
	/** All the items inside the bag */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "items")
		TArray<FItem> items;
	/** the limit of items that can be in the bag */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "items")
		int32 bagLimit;
	
private:
	/** The mesh of the bag */
	UPROPERTY(EditAnywhere, category = "mesh")
		UStaticMeshComponent* staticMesh;
	/** The pivot of the object */
	UPROPERTY(EditAnywhere, category = "mesh")
		UArrowComponent* arrow;
	/** The position and the rotation of the mesh at start */
	FVector beginPos;
	FRotator beginRot;
};
