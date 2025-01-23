// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    Orb = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Orb"));
    Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring"));

    SetRootComponent(Box);
    Orb->SetupAttachment(Box);
    Ring->SetupAttachment(Orb);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> OrbMesh(TEXT("/Game/StackOBot/Environment/Props/SM_GenericPlayerPickup_Core.SM_GenericPlayerPickup_Core"));
    if (OrbMesh.Succeeded())
    {
        Orb->SetStaticMesh(OrbMesh.Object);
        UE_LOG(LogTemp, Warning, TEXT("Orb Mesh"));
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> RingMesh(TEXT("/Game/StackOBot/Environment/Props/SM_GenericPlayerPickup_Ring.SM_GenericPlayerPickup_Ring"));
    if (RingMesh.Succeeded())
    {
        Ring->SetStaticMesh(RingMesh.Object);
        UE_LOG(LogTemp, Warning, TEXT("Ring Mesh"));
    }
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (Orb)
    {
        //Orb->AddLocalRotation(FRotator(DeltaTime * 100, DeltaTime * 100, 0));
        Ring->AddLocalRotation(FRotator(DeltaTime * 100, 0, 0));
    }
}

