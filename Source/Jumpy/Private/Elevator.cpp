// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ElevatorBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	Root->SetupAttachment(GetRootComponent());
	ElevatorMesh->SetupAttachment(Root);
	ElevatorBoxCollision->SetupAttachment(ElevatorMesh);
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	
	GetWorldTimerManager().SetTimer(TimerForStayingDown, this, &AElevator::SetGoToEndLocation, TimeToStayDown, false);

	ElevatorBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnBeginElavatorOverlap);
	ElevatorBoxCollision->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnEndElevatorOverlap);
}

void AElevator::SetGoToEndLocation()
{
	GoToEndLocation = true;
	GoToStartLocation = false;
}

void AElevator::OnBeginElavatorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hehehe"));
	IsPlayerOut = false;

	GetWorldTimerManager().SetTimer(TimerForStayingUp, this, &AElevator::SetGoToStartLocation, TimeToStayUp, false);
}

void AElevator::OnEndElevatorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsPlayerOut = true;

	GetWorldTimerManager().SetTimer(TimerForStayingDown, this, &AElevator::SetGoToEndLocation, TimeToStayDown, false);
}

void AElevator::SetGoToStartLocation()
{
	//UE_LOG(LogTemp, Warning, TEXT("SetGoToStartLocation"));
	GoToEndLocation = false;
	GoToStartLocation = true;
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GoToEndLocation)
	{
		if (IsPlayerOut)
		{
			FVector TempLocation = UKismetMathLibrary::VInterpTo(ElevatorMesh->GetRelativeLocation(), EndLocation, DeltaTime, 2);
			ElevatorMesh->SetRelativeLocation(TempLocation);

			double DistanceToEndLocation = UKismetMathLibrary::Vector_Distance(TempLocation, EndLocation);
			if (DistanceToEndLocation < 20)
			{
				GoToEndLocation = false;
			}
		}
		
	}

	if(GoToStartLocation)
	{
		FVector TempLocation = UKismetMathLibrary::VInterpTo(ElevatorMesh->GetRelativeLocation(), StartLocation, DeltaTime, 2);
		ElevatorMesh->SetRelativeLocation(TempLocation);

		double DistanceToStartLocation = UKismetMathLibrary::Vector_Distance(TempLocation, StartLocation);
		if (DistanceToStartLocation < 20)
		{
			GoToStartLocation = false;
		}
	}
}

