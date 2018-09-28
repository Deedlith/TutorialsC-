// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "TutoDataBase.h"
#include "TutoWeapon.generated.h"



class ATutoPlayer;

UCLASS()
class TUTOINVENTAIRE_API ATutoWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutoWeapon();
	ATutoWeapon(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

	void Reload();

	void FullMagazine(); //reload full charger

	void Equip(ATutoPlayer* player);

	ATutoPlayer* owner;

	//events
	bool isReloading;
	float currentTimeReloading;
	bool canFire;
	float currentCoolDownFire;

#pragma region stats
	//Weapon Information
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FWeapon info;
	//stats weapon
	//FString name;
	//float fireRate; //time between fire (plus il est bas plus on tire vite)
	//int bulletPerMagazine; //Nb balles max par chargeur
	//int currentBullet; // nb bullet in magazine (current)
	//int totalBullet; // nb bullet on me
	//int damage; // damage of weapon
	//float weaponRange; // range for fire
	//float reloadTime; // time of reloading

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		int GetCurrentBullet();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		int GeTotalBullet();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		bool IsReloading();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetFireRate();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		int GetBulletPerMagazine();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		int GetDamage();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetWeaponRange();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetReloadTime();


#pragma endregion stats

	//Components of weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UBoxComponent* triggerPickUp; //Box for getting weapon from the ground
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		USkeletalMeshComponent* mesh;//mesh for visual aspect of weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UArrowComponent* fireStart; //place from bullet came

	
};
