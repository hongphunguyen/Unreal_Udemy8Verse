// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacterCPP.h"

// Sets default values
AVRCharacterCPP::AVRCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // Create Root Component
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
    RootComponent->SetupAttachment(GetRootComponent());
    // Left Motion Controller
    LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
    LeftController->SetupAttachment(RootComponent);
    LeftController->SetTrackingSource(EControllerHand::Left);
    // Right Motion Controller
    RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
    RightController->SetupAttachment(RootComponent);
    RightController->SetTrackingSource(EControllerHand::Right);
}

// Called when the game starts or when spawned
void AVRCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

