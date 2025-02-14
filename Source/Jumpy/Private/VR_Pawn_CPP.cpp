// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Pawn_CPP.h"

// Sets default values
AVR_Pawn_CPP::AVR_Pawn_CPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create Root Component
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
    RootComponent->SetupAttachment(GetRootComponent());

    // Create VRMesh
    VRStaticMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VRMesh"));
    VRStaticMesh->SetupAttachment(RootComponent);

    // Create Collision
    VRCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    VRCollision->SetupAttachment(VRStaticMesh);

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
void AVR_Pawn_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVR_Pawn_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVR_Pawn_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

