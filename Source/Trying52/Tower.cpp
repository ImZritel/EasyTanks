// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (TankPtr) {
        float Distance = FVector::Dist(GetActorLocation(), TankPtr->GetActorLocation());
        
        if (Distance <= FireRange) {
            RotateTurret(TankPtr->GetActorLocation());
        }
    }
}

void ATower::BeginPlay() {
    Super::BeginPlay();

    TankPtr = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition() {
    if (TankPtr && TankPtr->bAlive) {
        float Distance = FVector::Dist(GetActorLocation(), TankPtr->GetActorLocation());
            
        if (Distance <= FireRange) {
            Fire();
        }
    }    
}

void ATower::HandleDestruction() {
    Super::HandleDestruction();

    Destroy();
}