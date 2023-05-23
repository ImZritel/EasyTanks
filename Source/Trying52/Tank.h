// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TRYING52_API ATank : public ABasePawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Components (CPP)")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components (CPP)")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement (CPP)", meta = (AllowPrivateAccess = "true"))
	float Speed = 350.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement (CPP)", meta = (AllowPrivateAccess = "true"))
	float TurnRate = 50.f;

	// functions:
	void Move(float Value);
	void Turn(float Value);

	// service variables:
	APlayerController* PlayerControllerPtr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Constructor:
	ATank(); 

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const {return PlayerControllerPtr;};

	bool bAlive = true;
};
