// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "VRCharacterCPP.generated.h"

UCLASS()
class JUMPY_API AVRCharacterCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacterCPP();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	class UCameraComponent* VRCamera;

	// Motion Controllers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	class UMotionControllerComponent* LeftController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	class UMotionControllerComponent* RightController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
