// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//UPROPERTY variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Control", meta = (AllowPrivateAccess = "true"))
	float DangerClose = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Control", meta = (AllowPrivateAccess = "true"))
	float ViewDistance = 1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Control", meta = (AllowPrivateAccess = "true"))
	float FireRange = 3000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Control", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;

	//variables
	class ATank* PlayerPawn;

	//functions
	FVector GetPlayerLocation();
	float GetPlayerDistance();
};
