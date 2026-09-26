// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ZOMBIE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	bool isMovingForward;
	bool isMovingBackward;
	bool isMovingLeft;
	bool isMovingRight;
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "input")
	UInputMappingContext* playerMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "input")
	UInputAction* playerMoveForwardAction;
	UPROPERTY(EditDefaultsOnly, Category = "input")
	UInputAction* playerMoveBackwardAction;
	UPROPERTY(EditDefaultsOnly, Category = "input")
	UInputAction* playerMoveLeftAction;
	UPROPERTY(EditDefaultsOnly, Category = "input")
	UInputAction* playerMoveRightAction;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Called to check when binds are released
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

	//Called to check when binds are released
	void MoveForwardReleased();
	void MoveBackwardReleased();
	void MoveLeftReleased();
	void MoveRightReleased();
};
