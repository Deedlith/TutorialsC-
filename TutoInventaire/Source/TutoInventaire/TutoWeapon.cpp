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
	initWithRandom = false;
	isReloading = false;
	currentTimeReloading = 0.0f;
	canFire = true;

	fireRate = 1.0f;
	bulletPerMagazine = 10;
	currentBullet = bulletPerMagazine;
	totalBullet = 10;
	damage = 10;
	weaponRange = 200.0f;
	reloadTime = 2.0f;

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

	if (initWithRandom)
		Init();
	
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
		if (currentTimeReloading >= reloadTime)
		{
			isReloading = false;
			FullMagazine();
		}
	}

	if (!canFire)
	{
		currentCoolDownFire += DeltaTime;
		if (currentCoolDownFire >= fireRate)
			canFire = true;
	}
}

void ATutoWeapon::Fire()
{
	if (!isReloading && canFire && owner)
	{
		currentBullet--;
		currentCoolDownFire = 0.0;
		canFire = false;

		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.bTraceAsyncScene = true;
		RV_TraceParams.bReturnPhysicalMaterial = false;

		//Re-Init hit info
		FHitResult RV_Hit(ForceInit);

		FVector startFire = fireStart->GetComponentLocation();
		FVector endFire = startFire + (owner->GetActorRotation().Vector() * weaponRange);

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

		if (currentBullet <= 0)
		{
			Reload();
		}
	}
}

void ATutoWeapon::Reload() 
{

	if (!isReloading && currentBullet < bulletPerMagazine)
	{
		isReloading = true;
		currentTimeReloading = 0.0f;
	}
}

void ATutoWeapon::Init() 
{
	fireRate = FMath::RandRange(0.1f, 1.0f);
	bulletPerMagazine = FMath::RandRange(10, 20);
	currentBullet = bulletPerMagazine;
	totalBullet = FMath::RandRange(50, 200);
	damage = FMath::RandRange(10, 100);
	weaponRange = FMath::RandRange(100.0f, 500.0f);
	reloadTime = FMath::RandRange(1.0f, 3.0f);
}

void ATutoWeapon::FullMagazine() 
{
	int missingBullets = bulletPerMagazine - currentBullet;

	if (totalBullet - missingBullets > 0)
	{
		currentBullet += missingBullets;
		totalBullet -= missingBullets;
	}
	else
	{
		currentBullet += totalBullet;
		totalBullet = 0;
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
	return currentBullet;
}


int ATutoWeapon::GeTotalBullet() 
{
	return totalBullet;
}


bool ATutoWeapon::IsReloading() 
{
	return isReloading;
}

float ATutoWeapon::GetFireRate() 
{
	return fireRate;

}

int ATutoWeapon::GetBulletPerMagazine() 
{
	return bulletPerMagazine;
}


int ATutoWeapon::GetDamage() {
	return damage;
}


float ATutoWeapon::GetWeaponRange() {
	return weaponRange;
}


float ATutoWeapon::GetReloadTime() {
	return reloadTime;
}

#pragma endregion stats