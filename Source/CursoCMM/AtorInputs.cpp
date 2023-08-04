// Fill out your copyright notice in the Description page of Project Settings.


#include "AtorInputs.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AAtorInputs::AAtorInputs()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetSimulatePhysics(true);
	RootComponent = StaticMesh;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Minha Câmera"));
	Camera->SetupAttachment(RootComponent);
	Camera->AddRelativeLocation(FVector(-330.f, 0.f, 130.f));

}

// Called when the game starts or when spawned
void AAtorInputs::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAtorInputs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAtorInputs::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &AAtorInputs::MoveVerticalmente);
	PlayerInputComponent->BindAxis("Horizontal", this, &AAtorInputs::MoveHorizontalmente);
	PlayerInputComponent->BindAxis("MouseX", this, &AAtorInputs::RotacionaEmZ);

}

void AAtorInputs::MoveVerticalmente(float eixoVertical)
{
	FVector PosicaoAtual = GetActorLocation();
	FVector Frente = GetActorForwardVector();
	SetActorLocation(PosicaoAtual + (Frente * eixoVertical));
}

void AAtorInputs::MoveHorizontalmente(float eixoHorizontal)
{
	FVector PosicaoAtual = GetActorLocation();
	FVector Right = GetActorRightVector();
	SetActorLocation(PosicaoAtual + (Right * eixoHorizontal));
}

void AAtorInputs::RotacionaEmZ(float rotacaoZ)
{
	FRotator RotacaoAtual = GetActorRotation();
	FRotator eixoZ = FRotator::MakeFromEuler(FVector (0.f, 0.f, 1.f));
	SetActorRotation(RotacaoAtual + (eixoZ * rotacaoZ));

}
