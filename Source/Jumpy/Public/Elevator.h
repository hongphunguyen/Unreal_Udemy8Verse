// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Elevator.generated.h"

UCLASS()
class JUMPY_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = true))
	FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = true))
	FVector EndLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ElevatorMesh;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ElevatorBoxCollision;

	FTimerHandle TimerForStayingDown;
	FTimerHandle TimerForStayingUp;

	UFUNCTION()
	void SetGoToEndLocation();
	UFUNCTION()
	void SetGoToStartLocation();

	UPROPERTY(EditAnywhere)
	float TimeToStayDown = 2;
	UPROPERTY(EditAnywhere)
	float TimeToStayUp = 2;

	bool GoToEndLocation = false;
	bool GoToStartLocation = false;
	bool IsPlayerOut = true;

	UFUNCTION()
	void OnBeginElavatorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndElevatorOverlap(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
