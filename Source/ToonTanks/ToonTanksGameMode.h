// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	//functions
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	//blueprint defined functions
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	//variables
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;
	int32 TargetTowers = 0;

	//UPROPERTY variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Control", meta = (AllowPrivateAccess = "true"))
	float StartDelay = 3.f;

	//functions
	void HandleGameStart();
	int32 GetTargetTowerCount();
};