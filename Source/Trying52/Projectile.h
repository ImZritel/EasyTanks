// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TRYING52_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Fire")
	class UProjectileMovementComponent* ProjectileMovementComp;
	UPROPERTY(VisibleAnywhere, Category = "Fire")
	float InitialSpeed = 1000.f;
	UPROPERTY(VisibleAnywhere, Category = "Fire")
	float MaxSpeed = 2000.f;
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystemComponent* FlowParticles;
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* FireSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse,
		const FHitResult& Hit 
	);

public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
