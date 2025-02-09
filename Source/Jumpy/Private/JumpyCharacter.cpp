// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "JumpyCharacter.h"

// Sets default values
AJumpyCharacter::AJumpyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 500;
	SpringArm->SocketOffset = FVector(0, 0, 120);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	//Camera->SetupAttachment(SpringArm);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AJumpyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Begin play"));

	/*UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), (bExampleBool ? TEXT("true") : TEXT("false")));
	UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), ExampleInteger);
	UE_LOG(LogTemp, Warning, TEXT("Current values are: vector %s, float %f, and integer %d"), *ExampleVector.ToString(), ExampleFloat, ExampleInteger);*/

	APlayerController* JumpyController = Cast<APlayerController>(GetController());

	if (JumpyController)
	{
		PlayerHUD = CreateWidget<UJumpyUI>(JumpyController, widgetSubclass);
		PlayerHUD->AddToViewport();

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(JumpyController->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMCJumpy, 0);
		}
	}

	UWorld* World = GetWorld();
	if (World)
	{
		int32 IncreaseValue = 0;

		for (int32 i = 0; i < 100; i++)
		{

			//FVector SpawnLocation = FVector(UKismetMathLibrary::RandomFloatInRange(-1000, 1000) * 2, UKismetMathLibrary::RandomFloatInRange(-1000, 1000) * 2, 70.0f);
			FVector SpawnLocation = FVector(0, i * 100, 70.0f);
			FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AItem* SpawnedItem = World->SpawnActor<AItem>(AItem::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
			
			if (SpawnedItem)
			{
				SpawnedItem->ItemValue = IncreaseValue++;
				SpawnedItem->SetItemValue(SpawnedItem->ItemValue);
			}
		}
	}
}



// Called every frame
void AJumpyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerHUD)
	{
		PlayerHUD->SetText(GetActorLocation().Z);
	}
}

// Called to bind functionality to input
void AJumpyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &AJumpyCharacter::Move);
		EnhancedInputComponent->BindAction(IALook, ETriggerEvent::Triggered, this, &AJumpyCharacter::Look);
		EnhancedInputComponent->BindAction(IAJump, ETriggerEvent::Started, this, &AJumpyCharacter::Jumping);
	}
}

void AJumpyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D RCValue = Value.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *RCValue.ToString());

	FRotator ControlRotation = GetControlRotation();
	
	FVector ForwardVector = FRotationMatrix(FRotator(0, ControlRotation.Yaw, 0)).GetUnitAxis(EAxis::X);
	//FVector RightVector = FRotationMatrix(FRotator(0, ControlRotation.Yaw, ControlRotation.Roll)).GetUnitAxis(EAxis::Y);
	FVector RightVector = FRotationMatrix(FRotator(0, ControlRotation.Yaw, 0)).GetUnitAxis(EAxis::Y);

	//FVector ForwardVector = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardVector, RCValue.Y);
	AddMovementInput(RightVector, RCValue.X);
}

void AJumpyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D RCValue = Value.Get<FVector2D>();
	
	AddControllerPitchInput(RCValue.Y);
	AddControllerYawInput(RCValue.X);
}

void AJumpyCharacter::Jumping(const FInputActionValue& Value)
{
	Jump();
}

