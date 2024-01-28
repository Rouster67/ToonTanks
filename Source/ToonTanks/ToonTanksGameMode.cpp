// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        //destroys tank actor
        Tank->HandleDestruction();
        //disables player input
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        //ends the game as a loss
        GameOver(false);
        
    } else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        //destroys the tower
        DestroyedTower->HandleDestruction();
        //Subtracts 1 tower
        --TargetTowers;
        //Ends the game as a win if all towers are destroyed
        if(TargetTowers <= 0)
            GameOver(true);
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    //gets the amount of towers in the level
    TargetTowers = GetTargetTowerCount();
    //gets the player controlled tank
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    //gets the player controller
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    //calls blueprint implemented start game function
    StartGame();


    if(ToonTanksPlayerController)
    {
        //disables player controll
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        //decalres FTimerHandle
        FTimerHandle PlayerEnableTimerHandle;

        //sets delegate to call SetPlayerEnabledState
        FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );

        //calls delegate after StartDelay
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnabledTimerDelegate,
            StartDelay,
            false
        );
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    //Creates Empty Array
    TArray<AActor*> Towers;
    //Stores all Towers in Array
    UGameplayStatics::GetAllActorsOfClass(
        this,
        ATower::StaticClass(),
        Towers
    );

    //returns the number of towers
    return Towers.Num();
}