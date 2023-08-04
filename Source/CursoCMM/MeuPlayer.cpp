// Fill out your copyright notice in the Description page of Project Settings.


#include "MeuPlayer.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AMeuPlayer::AMeuPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParticulaGranada = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particula"));
	ParticulaGranada->bAutoActivate = false;
	ParticulaGranada->bAutoDestroy = false;
	ParticulaGranada->SetupAttachment((USceneComponent*)GetMesh());
	
}

// Called when the game starts or when spawned
void AMeuPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeuPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMeuPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

