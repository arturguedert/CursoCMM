// Fill out your copyright notice in the Description page of Project Settings.


#include "MinhaClasseUnreal.h"

// Sets default values
AMinhaClasseUnreal::AMinhaClasseUnreal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinhaClasseUnreal::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log("Minha Classe Curso C++ Unreal");

}

// Called every frame
void AMinhaClasseUnreal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

