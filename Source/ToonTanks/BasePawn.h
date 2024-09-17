// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();
	

protected:

	void RotateTurret(FVector LookAtTarget);

	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Varialbes", meta = (AllowPrivateAccess = "true"))
    class UCapsuleComponent* CaspuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Varialbes", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Varialbes", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Varialbes", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjecttileSpawnPoint;



	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
};
