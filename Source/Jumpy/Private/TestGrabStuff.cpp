// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGrabStuff.h"

// Sets default values
ATestGrabStuff::ATestGrabStuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestGrabStuffMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestGrabStuffMesh"));
	RootComponent = TestGrabStuffMesh;
}

// Called when the game starts or when spawned
void ATestGrabStuff::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestGrabStuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}