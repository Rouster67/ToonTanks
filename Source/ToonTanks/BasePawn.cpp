// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule Component and set as Root
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	// Create Base Mesh and attach to Root
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	// Create Turret Mesh and attach to Base Mesh
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// Create Projectile Spawn Point and attach to Turret Mesh
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//Calculates the rotation needed to face the target
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	//Converts the vector to a rotator
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	//Interpolates the rotation
	FRotator InterpRotation = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		SwivelSpeed
	);
	
	//Sets the turret rotation
	TurretMesh->SetWorldRotation(InterpRotation);
}
