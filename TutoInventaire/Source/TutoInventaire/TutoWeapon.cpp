// Fill out your copyright notice in the Description page of Project Settings.

#include "TutoWeapon.h"
#include "TutoPlayer.h"


// Sets default values
ATutoWeapon::ATutoWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ATutoWeapon::ATutoWeapon(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	owner = nullptr;
	isReloading = false;
	currentTimeReloading = 0.0f;
	canFire = true;

	/**
	 * Le BoxComponent va être la racine de notre objet, c'est lui qui va gérer la récupération de notre
arme. Le mesh sera en enfant et la flèche tout à la fin afin qu'elle suive l'arme.
	 */
	triggerPickUp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerPickUp"));
	RootComponent = triggerPickUp;

	mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("mesh"));
	mesh->SetupAttachment(RootComponent);

	fireStart = ObjectInitializer.CreateDefaultSubobject<UArrowComponent>(this, TEXT("FireStart"));
	fireStart->SetupAttachment(mesh);

}

// Called when the game starts or when spawned
void ATutoWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
/*
Je vous conseil de ne l'utiliser que pour récupérer des inputs et gérer
des timers car trop gourmande
*/
void ATutoWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isReloading)
	{
		currentTimeReloading += DeltaTime;
		if (currentTimeReloading >= info.reloadTime)
		{
			isReloading = false;
			FullMagazine();
		}
	}

	if (!canFire)
	{
		currentCoolDownFire += DeltaTime;
		if (currentCoolDownFire >= info.fireRate)
			canFire = true;
	}
}

void ATutoWeapon::Fire()
{
	if (!isReloading && canFire && owner)
	{
		info.currentBullet--;
		currentCoolDownFire = 0.0;
		canFire = false;

		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.bTraceAsyncScene = true;
		RV_TraceParams.bReturnPhysicalMaterial = false;

		//Re-Init hit info
		FHitResult RV_Hit(ForceInit);

		FVector startFire = fireStart->GetComponentLocation();
		FVector endFire = startFire + (owner->GetActorRotation().Vector() * info.weaponRange);

		//call GetWorld() from within an actor extending class
		GetWorld()->LineTraceSingleByChannel(

			RV_Hit,
			startFire,
			endFire,
			ECC_Camera,
			RV_TraceParams
		);

		//in a non-Static class
		//Draw the Line !
		DrawDebugLine(GetWorld(), startFire, endFire, FColor(255 ,0, 0), false, 1.0f, 0, 1.0f);

		if (RV_Hit.GetActor())
		{
			ATutoPlayer* enemyHit = Cast<ATutoPlayer>(RV_Hit.GetActor());
			if (enemyHit)
				UE_LOG(LogTemp, Warning, TEXT("Enemy HIT ! "));
		}

		if (info.currentBullet <= 0)
		{
			Reload();
		}
	}
}

void ATutoWeapon::Reload() 
{

	if (!isReloading && info.currentBullet < info.bulletPerMagazine)
	{
		isReloading = true;
		currentTimeReloading = 0.0f;
	}
}


void ATutoWeapon::FullMagazine() 
{
	int missingBullets = info.bulletPerMagazine - info.currentBullet;

	if (info.totalBullet - missingBullets > 0)
	{
		info.currentBullet += missingBullets;
		info.totalBullet -= missingBullets;
	}
	else
	{
		info.currentBullet += info.totalBullet;
		info.totalBullet = 0;
	}
}

void ATutoWeapon::Equip(ATutoPlayer* player) 
{
	if (!owner)
	{
		owner = player;
	}
}

#pragma region stats
int ATutoWeapon::GetCurrentBullet() 
{
	return info.currentBullet;
}


int ATutoWeapon::GeTotalBullet() 
{
	return info.totalBullet;
}


bool ATutoWeapon::IsReloading() 
{
	return isReloading;
}

float ATutoWeapon::GetFireRate() 
{
	return info.fireRate;

}

int ATutoWeapon::GetBulletPerMagazine() 
{
	return info.bulletPerMagazine;
}


int ATutoWeapon::GetDamage() {
	return info.damage;
}


float ATutoWeapon::GetWeaponRange() {
	return info.weaponRange;
}


float ATutoWeapon::GetReloadTime() {
	return info.reloadTime;
}

#pragma endregion stats