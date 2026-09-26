// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	isMovingForward = false;
	isMovingBackward = false;
	isMovingLeft = false;
	isMovingRight = false;
	
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

	// Stops conflicting movement
	if (isMovingForward && !isMovingBackward)
	{
		AddMovementInput(GetActorForwardVector(), 1.0f);
	}
	if (isMovingBackward && !isMovingForward)
	{
		AddMovementInput(-GetActorForwardVector(), 1.0f);
	}
	if (isMovingLeft && !isMovingRight)
	{
		AddMovementInput(-GetActorRightVector(), 1.0f);
	}
	if (isMovingRight && !isMovingLeft)
	{
		AddMovementInput(GetActorRightVector(), 1.0f);
	}
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
	// Bind movement actions for held and released input.
	enhancedInputComponent->BindAction(playerMoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
	enhancedInputComponent->BindAction(playerMoveBackwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveBackward);
	enhancedInputComponent->BindAction(playerMoveLeftAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveLeft);
	enhancedInputComponent->BindAction(playerMoveRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);

	enhancedInputComponent->BindAction(playerMoveForwardAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveForwardReleased);
	enhancedInputComponent->BindAction(playerMoveBackwardAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveBackwardReleased);
	enhancedInputComponent->BindAction(playerMoveLeftAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveLeftReleased);
	enhancedInputComponent->BindAction(playerMoveRightAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveRightReleased);
}

//Track triggered directions for movement state.
void APlayerCharacter::MoveForward()
{
	isMovingForward = true;
}
void APlayerCharacter::MoveBackward()
{
	isMovingBackward = true;
}
void APlayerCharacter::MoveLeft()
{
	isMovingLeft = true;
}
void APlayerCharacter::MoveRight()
{
	isMovingRight = true;
}

//Track released directions for movement state.
void APlayerCharacter::MoveForwardReleased()
{
	isMovingForward = false;
}
void APlayerCharacter::MoveBackwardReleased()
{
	isMovingBackward = false;
}
void APlayerCharacter::MoveLeftReleased()
{
	isMovingLeft = false;
}
void APlayerCharacter::MoveRightReleased()
{
	isMovingRight = false;
}