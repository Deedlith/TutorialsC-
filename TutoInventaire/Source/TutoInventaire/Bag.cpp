// Fill out your copyright notice in the Description page of Project Settings.

#include "Bag.h"
#include "TutoItem.h"

// Sets default values
ABag::ABag()
{
 	PrimaryActorTick.bCanEverTick = false;
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("mesh component"));
	arrow = CreateDefaultSubobject<UArrowComponent>(FName("arrow component"));
	RootComponent = arrow;
	staticMesh->SetupAttachment(arrow);
}

// Called when the game starts or when spawned
void ABag::BeginPlay()
{
	Super::BeginPlay();
	beginPos = staticMesh->GetRelativeTransform().GetLocation();
	beginRot = staticMesh->GetRelativeTransform().GetRotation().Rotator();
	staticMesh->SetSimulatePhysics(true);
	
}

// Called every frame
void ABag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABag::AddItem(ATutoItem* theItem)
{
	if (items.Num() < bagLimit)
	{
		items.Add(theItem->info);
		theItem->Destroy();
	}
}
void ABag::OnConstruction(const FTransform& Transform)
{
	// Create a new random color on the bag
	FVector color = FVector(FMath::RandRange(0.f, 1.f), FMath::RandRange(0.f, 1.f),
		FMath::RandRange(0.f, 1.f));
	// Set the color on the material
	staticMesh->SetVectorParameterValueOnMaterials(FName("Color"), color);
	bagLimit = FMath::RandRange(5, 10);
}
void ABag::DisableCollisions()
{
	staticMesh->SetSimulatePhysics(false);
	staticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	staticMesh->AttachTo(arrow, NAME_None, EAttachLocation::KeepWorldPosition);
	staticMesh->SetRelativeLocation(beginPos);
	staticMesh->SetRelativeRotation(beginRot);
}
void ABag::EnableCollisions()
{
	staticMesh->SetSimulatePhysics(true);
	staticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

