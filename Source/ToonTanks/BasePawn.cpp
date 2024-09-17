// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CaspuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Caps Collider"));
	RootComponent = CaspuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	BaseMesh -> SetupAttachment(CaspuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret mesh"));
	TurretMesh -> SetupAttachment(BaseMesh);

	ProjecttileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjecttileSpawnPoint -> SetupAttachment(TurretMesh);
}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{

	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh -> SetWorldRotation(FMath::RInterpTo(TurretMesh-> GetComponentRotation(), LookAtRotation, 
	UGameplayStatics::GetWorldDeltaSeconds(this), 5.f));
}

void ABasePawn::Fire()
{

	FVector Location = ProjecttileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjecttileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld() -> SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);

	Projectile -> SetOwner(this);


}

void ABasePawn::HandleDestruction()
{

	
}

