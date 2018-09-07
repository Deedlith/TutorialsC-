// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TutoInventaire.h"

//USTRUCT(BlueprintType)
//struct FRequirement
//{
//	GENERATED_USTRUCT_BODY()
//
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirement")
//		int32 ID;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirement")
//		int32 Quantity;
//
//	FRequirement()
//	{
//		ID = -1;
//		Quantity = 1;
//	}
//};
//
//USTRUCT(BlueprintType)
//struct FCraft
//{
//	GENERATED_USTRUCT_BODY()
//
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
//		int32 ID;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
//		int32 Quantity;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
//		TArray<FRequirement> Requirement;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
//		FString Name;
//
//	FCraft()
//	{
//		ID = -1;
//		Quantity = 1;
//		Name = "UNKNOWN";
//	}
//};

/**
 * 
 */
class TUTOINVENTAIRE_API Data
{
public:
	Data();
	~Data();
};
