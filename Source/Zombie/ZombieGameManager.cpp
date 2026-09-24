// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieGameManager.h"

// Sets default values
AZombieGameManager::AZombieGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void AZombieGameManager::StartGame()
{
	UE_LOG(LogTemp, Display, TEXT("Start Game Called!"));
}

// Called when the game starts or when spawned
void AZombieGameManager::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Zombie Game Started!"));
}

// Called every frame
void AZombieGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

