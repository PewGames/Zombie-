// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (!playerController)
	{
		return;
	}

	ULocalPlayer* localPlayer = playerController->GetLocalPlayer();
	if (!localPlayer)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem =
    ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
        localPlayer
    );
	if (!inputSubsystem)
	{
		return;
	}
	inputSubsystem->AddMappingContext(playerMappingContext, 0);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!enhancedInputComponent)
	{
		return;
	}
	enhancedInputComponent->BindAction(
		playerMoveAction,
		ETriggerEvent::Triggered,
		this,
		&APlayerCharacter::Move
	);
}

// My Player Move Function
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D movementVector = Value.Get<FVector2D>();

	UE_LOG(LogTemp, Warning, TEXT("Move X: %f | Y: %f"), movementVector.X, movementVector.Y);

	AddMovementInput(GetActorForwardVector(), movementVector.Y);
	AddMovementInput(GetActorRightVector(), movementVector.X);
}

