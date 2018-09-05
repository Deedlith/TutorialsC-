// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "TutoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TUTOINVENTAIRE_API ATutoGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	ATutoGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
};
