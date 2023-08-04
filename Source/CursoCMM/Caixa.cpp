// Fill out your copyright notice in the Description page of Project Settings.


#include "Caixa.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"


// Sets default values
ACaixa::ACaixa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colisor = CreateDefaultSubobject<UBoxComponent>(FName("Colisor"));
	Colisor->SetNotifyRigidBodyCollision(true);
	Colisor->SetSimulatePhysics(true);
	Colisor->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	Colisor->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	Colisor->InitBoxExtent(FVector(55.f, 30.f, 30.f));
	RootComponent = Colisor;
	Colisor->OnComponentHit.AddDynamic(this, &ACaixa::OcorreuHitNoComponente);
	
	this->OnActorHit.AddDynamic(this, &ACaixa::OcorreuHitNoAtor);

	MalhaDaCaixa = CreateDefaultSubobject<UStaticMeshComponent>(FName("Malha"));
	MalhaDaCaixa->SetupAttachment(RootComponent);

	
	SomDoHit = CreateDefaultSubobject<UAudioComponent>(FName("Som do Hit"));
	SomDoHit->bAutoActivate = false;
	SomDoHit->bStopWhenOwnerDestroyed = false;
	SomDoHit->SetupAttachment(RootComponent);

	ParticulaHit = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particula"));
	ParticulaHit->bAutoActivate = false;
	ParticulaHit->SetupAttachment(RootComponent);
}

void ACaixa::OcorreuHitNoComponente(UPrimitiveComponent* HitComponent, AActor* OtheActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (!bDeuHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit")));
		if ((OtheActor != nullptr) && (OtheActor != this) && (OtherComp != nullptr) && !(OtheActor->ActorHasTag(FName("Floor"))))
		{
			SomDoHit->Activate(true);
			SomDoHit->Play(0.0f);
			ParticulaHit->Activate(true);
			OtheActor->Destroy();
			
			
		}
		GetWorldTimerManager().SetTimer(Delay, this, &ACaixa::ResetExplosao, (.3f), false);
		bDeuHit = true;
	}
	
}

void ACaixa::OcorreuHitNoAtor(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ActorHit")));
}

void ACaixa::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool SelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("NotifyHit")));
}

void ACaixa::ResetExplosao()
{
	bDeuHit = false;
	GetWorldTimerManager().ClearTimer(Delay);
}

// Called when the game starts or when spawned
void ACaixa::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACaixa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

