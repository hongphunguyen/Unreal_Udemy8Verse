// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpyAnimationBluePrint.h"

void UJumpyAnimationBluePrint::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	jumpyCharacter = Cast<AJumpyCharacter>(TryGetPawnOwner());

	if (jumpyCharacter)
	{
		JumpyCharacterMovement = jumpyCharacter->GetCharacterMovement();
	}
}

void UJumpyAnimationBluePrint::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (JumpyCharacterMovement)
	{
		FVector VelocityVector = JumpyCharacterMovement->Velocity;

		PlayerSpeed = UKismetMathLibrary::VSizeXY(VelocityVector);

		// Calculate lean amount
		CurrentFrameRotation = jumpyCharacter->GetActorRotation();

		FRotator deltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(LastFrameRotation, CurrentFrameRotation);

		LeanAmount = UKismetMathLibrary::FInterpTo(LeanAmount, deltaRotator.Yaw, DeltaSeconds, 2);

		LastFrameRotation = jumpyCharacter->GetActorRotation();

		// Jump feature
		isInAir = JumpyCharacterMovement->IsFalling();
		FVector lastInputVector = jumpyCharacter->GetLastMovementInputVector();
		double movementInputValue = UKismetMathLibrary::VSize(lastInputVector);

		if (movementInputValue > 0)
			lastMovementInput = true;
		else
			lastMovementInput = false;
	}
}


