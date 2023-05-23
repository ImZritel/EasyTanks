// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TRYING52_API ATower : public ABasePawn
{
	GENERATED_BODY()

private:
	class ATank* TankPtr;

	UPROPERTY(EditAnywhere, Category="Combat")
	float FireRange{1000.f};
	
	FTimerHandle FireRateTimerHandle;
	float FireRate {2.f};
	void CheckFireCondition();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
};
