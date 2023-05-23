// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank() {
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm."));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera."));
    
    SpringArm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);    // specific axis mapping determined by its name, given in TEXT
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value) {
    //UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
    
    FVector offset(0.f);
    offset.X = Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AActor::AddActorLocalOffset(Value*offset, true);

}

void ATank::Turn(float Value) {
    // here is a lack of accounting of wether the tank moves forward or backward
    FRotator DeltaRotation(FRotator::ZeroRotator);
    DeltaRotation.Yaw = TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AActor::AddActorLocalRotation(Value * DeltaRotation, true);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    PlayerControllerPtr = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // draw debug sphere under cursor
    if(PlayerControllerPtr) {
        FHitResult HitResult;
        PlayerControllerPtr->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        
        /*DrawDebugSphere(
            GetWorld(), 
            HitResult.ImpactPoint,
            50.f,
            4,
            FColor::Green,
            false,
            -1.f
        );*/
    }
    // end draw debug sphere under cursor

    if(PlayerControllerPtr) {
        FHitResult HitResult;
        PlayerControllerPtr->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction() {
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}