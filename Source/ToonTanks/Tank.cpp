// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    //Setup SpringArm Component
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    //Setup Camera Component
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    //sets the player controller reference
    PlayerControllerRef = Cast<APlayerController>(GetController());
    if(PlayerControllerRef == nullptr)
        UE_LOG(LogTemp, Error, TEXT("Failed to get a valid APlayerController"));
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //rotates the turret to face the mouse cursor
    RotateTurret(GetMouseLocation());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Bind Axis
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float Value)
{
    //creates an empty vector
    FVector DeltaLocation(0.f);
    //gets the time between frames
    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    //sets the X axis of the vector
    DeltaLocation.X = Value * MoveSpeed * DeltaTime;

    //moves the tank
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{    
    //creates an empty rotator
    FRotator DeltaRotation(0.f);
    //gets the time between frames
    double DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    //sets the Yaw axis of the rotator
    DeltaRotation.Yaw = Value * TurnRate * DeltaTime;

    //rotates the tank
    AddActorLocalRotation(DeltaRotation, true);
}

FVector ATank::GetMouseLocation()
{
    if(PlayerControllerRef != nullptr)
    {
        //gets the hit result under the mouse cursor
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult
        );

        return HitResult.ImpactPoint;
    }else
    {  
        return FVector(0.f);
    }
}