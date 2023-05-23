// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// my
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile spawn point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}


void ABasePawn::RotateTurret(FVector TargetCoord) {
	FVector ToTarget = TargetCoord - TurretMesh->GetComponentLocation();
	FRotator RotationToTarget(0.f, ToTarget.Rotation().Yaw, 0.f);
	//TurretMesh->SetWorldRotation(RotationToTarget);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			RotationToTarget, 
			UGameplayStatics::GetWorldDeltaSeconds(this), 
			2.f
		)
	);
}

void ABasePawn::Fire() {
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
//	DrawDebugSphere(
//            GetWorld(), 
//            Location,
//            25.f,
//            16,
//            FColor::Red,
//            false,
//            3.f
//        );
}

void ABasePawn::HandleDestruction() {
	// TODO: visual/sound effects
		if (DeathParticleSystem) {
			UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticleSystem, GetActorLocation(), GetActorRotation());
		}
		if (DeathSound) {
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
		}
		if (DeathCameraShakeClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
		}
}