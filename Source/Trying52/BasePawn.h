// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TRYING52_API ABasePawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components (CPP)", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components (CPP)", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components (CPP)", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components (CPP)", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death animation.", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* DeathParticleSystem;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;



	UPROPERTY(EditDefaultsOnly, Category = "Projectile (CPP)")
	TSubclassOf<class AProjectile> ProjectileClass;     // stores the type of our projectile to be spawned
protected:
	void RotateTurret(FVector TargetCoord);
	void Fire();

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();
};
