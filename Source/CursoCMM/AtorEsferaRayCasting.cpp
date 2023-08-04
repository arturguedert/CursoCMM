// Fill out your copyright notice in the Description page of Project Settings.


#include "AtorEsferaRayCasting.h"
#include "Components/BillboardComponent.h"
#include "DrawDebugHelpers.h"
#include "WorldCollision.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
AAtorEsferaRayCasting::AAtorEsferaRayCasting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UBillboardComponent* Billboard = CreateDefaultSubobject<UBillboardComponent>(FName("Billboard"));
	RootComponent = Billboard;


}

// Called when the game starts or when spawned
void AAtorEsferaRayCasting::BeginPlay()
{
	Super::BeginPlay();
	
	TArray <FHitResult> ResultadosColisao;
	float RaioDaEsfera = 200.f;

	FVector LocalizacaoDoAtor = GetActorLocation();
	FCollisionShape ColisaoEsferica = FCollisionShape::MakeSphere(RaioDaEsfera);
	FVector FinalDEsferaDebug = LocalizacaoDoAtor + (FVector(1, 1, 1) * RaioDaEsfera);

	DrawDebugSphere(GetWorld(), LocalizacaoDoAtor, ColisaoEsferica.GetSphereRadius(), 200, FColor::Red, true, -1.f, (uint8)0, 0.5f);

	bool OcorreuColisao = GetWorld()->SweepMultiByChannel(ResultadosColisao, LocalizacaoDoAtor, FinalDEsferaDebug, FQuat::Identity, ECollisionChannel::ECC_WorldStatic, ColisaoEsferica);

	if (OcorreuColisao)
	{
		for (auto& Colisoes : ResultadosColisao)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, (FName("Ator %s"), *Colisoes.GetActor()->GetName()));
		}
	}
}

// Called every frame
void AAtorEsferaRayCasting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

