// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
    if (DeadActor == Tank) {
        Tank->HandleDestruction();
        if (PlayerController) {
            //Tank->DisableInput(Tank->GetTankPlayerController());
            //Tank->GetTankPlayerController()->bShowMouseCursor = false;
            PlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    } else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) {
        DestroyedTower->HandleDestruction();
        --TargetTowers;
        if (TargetTowers == 0) {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay() {
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart() {
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (PlayerController) {
        PlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnabledTimer;
        FTimerDelegate PlayerTimerDelegate = FTimerDelegate::CreateUObject(PlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
        GetWorldTimerManager().SetTimer(PlayerEnabledTimer, PlayerTimerDelegate, StartDelay, false);

    }
}

int32_t AToonTanksGameMode::GetTargetTowerCount(){
    TArray<AActor*> TowerPtrs;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowerPtrs);
    return TowerPtrs.Num();
}