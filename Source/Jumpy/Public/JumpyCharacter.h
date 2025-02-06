// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "JumpyUI.h"
#include "JumpyCharacter.generated.h"

UCLASS()
class JUMPY_API AJumpyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJumpyCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> widgetSubclass;


	UJumpyUI* PlayerHUD;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "MyInput")
	UInputMappingContext* IMCJumpy;

	UPROPERTY(EditAnywhere, Category = "MyInput")
	UInputAction* IAMove;
	UPROPERTY(EditAnywhere, Category = "MyInput")
	UInputAction* IALook;
	UPROPERTY(EditAnywhere, Category = "MyInput")
	UInputAction* IAJump;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jumping(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
};
