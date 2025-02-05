// Fill out your copyright notice in the Description page of Project Settings.


#include "Fan.h"

// Sets default values
AFan::AFan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	Fan = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FanMesh"));
	FanGrating = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FanGratingMesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	ForceDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	Wind = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VisualEffects"));

	Frame->SetupAttachment(GetRootComponent());
	Fan->SetupAttachment(Frame);
	FanGrating->SetupAttachment(Frame);
	BoxCollision->SetupAttachment(Frame);
	ForceDirection->SetupAttachment(BoxCollision);
	Wind->SetupAttachment(Frame);
}

// Called when the game starts or when spawned
void AFan::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player = Cast<AJumpyCharacter>(Character);

	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AFan::OnPlayerExit);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AFan::OnPlayerEnter);
}

void AFan::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AJumpyCharacter* TempPlayer = Cast<AJumpyCharacter>(OtherActor);

	if (TempPlayer)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFan::PushPlayer, 0.01, true);
	}
}

void AFan::OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJumpyCharacter* TempPlayer = Cast<AJumpyCharacter>(OtherActor);

	if (TempPlayer)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AFan::PushPlayer()
{
	Player->LaunchCharacter(ForceDirection->GetForwardVector() * FrocePower, false, true);
}

// Called every frame
void AFan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Fan->AddLocalRotation(FRotator(0, 0, 4.5f));
}

