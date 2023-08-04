// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpAmmo.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APickUpAmmo::APickUpAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colisor = CreateDefaultSubobject<UBoxComponent>(FName("Colisor"));
	Colisor->InitBoxExtent(TamanhoColisor);
	Colisor->SetCollisionProfileName("Trigger");
	RootComponent = Colisor;

	ObjetoDoPickUp = CreateDefaultSubobject<UStaticMeshComponent>(FName("Objeto do PickUp"));
	ObjetoDoPickUp->SetRelativeLocation(FVector(0.f, 0.f, -16.f));
	ObjetoDoPickUp->SetupAttachment(RootComponent);

	SomDoPickUp = CreateDefaultSubobject<UAudioComponent>(FName("Som do PickUp"));
	SomDoPickUp->bAutoActivate = false;
	SomDoPickUp->SetupAttachment(RootComponent);

	Colisor->OnComponentBeginOverlap.AddDynamic(this, &APickUpAmmo::ColidiuComPickUp);

}

void APickUpAmmo::ColidiuComPickUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		SomDoPickUp->Activate(true);
		SomDoPickUp->bStopWhenOwnerDestroyed = false;
		SomDoPickUp->Play(0.0f);
		Destroy();
	}
}

// Called when the game starts or when spawned
void APickUpAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugBox(GetWorld(), GetActorLocation(), TamanhoColisor * GetActorScale3D(), GetActorQuat(), FColor::Red, true, -1, 0, 0.5f);

}

