// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArm -> SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera -> SetupAttachment(springArm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent -> BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent -> BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController -> GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false, 
            HitResult);

        
    RotateTurret(HitResult.ImpactPoint);


    }

}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

}


void ATank::BeginPlay()
{
    Super::BeginPlay();
    
    // Casting
    TankPlayerController = Cast<APlayerController>(GetController());

}

void ATank::Move(float Value)
{

    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation);



}

void ATank::Turn(float value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);

}