// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{

}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
    //get a reference to the player pawn and casts it to ATank
    PlayerPawn = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //find distance to the tank
    //check to see if the tank is in range
    //if in range rotate turret toward tank
    //check for obstacles between turret and tank
    //check fire conditions
    //fire

    //Checks to see if the player pawn is valid
    if(PlayerPawn)
    {
        //Rotates the turret to face the player if they are in view
        if(GetPlayerDistance() <= ViewDistance)
        {
            RotateTurret(GetPlayerLocation());
        }
    }
}

FVector ATower::GetPlayerLocation()
{
    if(PlayerPawn)
        return PlayerPawn->GetActorLocation();
    else
        return FVector(0.f);
}

float ATower::GetPlayerDistance()
{
    if(PlayerPawn)
        return FVector::Dist(GetPlayerLocation(), GetActorLocation());
    else
        return -1.0f;
}