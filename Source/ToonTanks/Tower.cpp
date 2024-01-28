// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

ATower::ATower()
{

}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
    //get a reference to the player pawn and casts it to ATank
    PlayerPawn = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
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
        if(InView())
        {
            RotateTurret(GetPlayerLocation());
        }
    }
}

void ATower::CheckFireCondition()
{
    if(PlayerPawn)
    {
        if(InFireRange() && !IsPlayerMasked() && PlayerPawn->bAlive)
        {
            Fire();
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

bool ATower::InView()
{
    if(PlayerPawn)
    {
        if(GetPlayerDistance() <= ViewDistance)
            return true;
    }
    return false;
}

bool ATower::InFireRange()
{
    if(PlayerPawn)
    {
        if(GetPlayerDistance() <= FireRange)
            return true;
    }
    return false;
}

bool ATower::IsPlayerMasked()
{
    if(PlayerPawn)
    {
        //draw a line trace from the projectile spawn point to the player
        FHitResult HitResult;
        GetWorld()->LineTraceSingleByChannel(HitResult, ProjectileSpawnPoint->GetComponentLocation(), GetPlayerLocation(), ECC_Visibility);
        //if the line trace hits something other than the player return true
        if(HitResult.GetActor() == Cast<AActor>(PlayerPawn))
            return false;
    }
    return true;
}