// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

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

void ABasePawn::HandleDestruction()
{
	//play death sound
	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DeathSound,
			GetActorLocation()
		);
	}

	//plays camera shake
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}

	//spawns explosion effect
	if(DeathEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathEffect,
			GetActorLocation(),
			GetActorRotation()
		);
	}	
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

void ABasePawn::Fire()
{
	if(ProjectileClass)
	{
		//Spawns a projectile at the spawn point and stores a reference to it
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation()
		);
		//Sets the projectile's owner to this pawn
		Projectile->SetOwner(this);
	}
}