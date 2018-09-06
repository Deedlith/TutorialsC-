// Fill out your copyright notice in the Description page of Project Settings.

#include "TutoItem.h"


// Sets default values
ATutoItem::ATutoItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ATutoItem::ATutoItem(const FObjectInitializer& ObjectInitializer)
{

}

// Called when the game starts or when spawned
void ATutoItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATutoItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutoItem::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{


}

void ATutoItem::OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
