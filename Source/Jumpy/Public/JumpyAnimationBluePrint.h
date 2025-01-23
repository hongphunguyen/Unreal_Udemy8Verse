// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JumpyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "JumpyAnimationBluePrint.generated.h"

/**
 * 
 */
UCLASS()
class JUMPY_API UJumpyAnimationBluePrint : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(BlueprintReadOnly)
	AJumpyCharacter* jumpyCharacter;
	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* JumpyCharacterMovement;


	// variables
	UPROPERTY(BlueprintReadOnly)
	double PlayerSpeed;
	UPROPERTY(BlueprintReadOnly)
	float LeanAmount;
	FRotator CurrentFrameRotation;
	FRotator LastFrameRotation;

	UPROPERTY(BlueprintReadOnly)
	bool isInAir;
	UPROPERTY(BlueprintReadOnly)
	bool lastMovementInput;
};
