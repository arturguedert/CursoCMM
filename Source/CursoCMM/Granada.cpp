// Fill out your copyright notice in the Description page of Project Settings.


#include "Granada.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "EngineUtils.h"
#include "UObject/UObjectIterator.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/SkeletalMeshActor.h"
#include "UObject/UObjectBaseUtility.h"
#include "MeuPlayer.h"



// Sets default values
AGranada::AGranada()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColisorDoAtor = CreateDefaultSubobject<USphereComponent>(FName("Colisor"));
	ColisorDoAtor->SetSphereRadius(12.f);
	ColisorDoAtor->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = ColisorDoAtor;

	MalhaDoAtor = CreateDefaultSubobject<UStaticMeshComponent>(FName("Malha"));
	MalhaDoAtor->SetRelativeLocation(FVector(4.f, 0.f, 0.f));
	MalhaDoAtor->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	MalhaDoAtor->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>Granada(TEXT("/Script/Engine.StaticMesh'/Game/Meshes/granada.granada'"));

	SomDaExplosao = CreateDefaultSubobject<UAudioComponent>(FName("Som da Explosao"));
	SomDaExplosao->bAutoActivate = false;
	SomDaExplosao->bAutoDestroy = true;
	SomDaExplosao->SetupAttachment(MalhaDoAtor);
	ConstructorHelpers::FObjectFinder<USoundCue>SomGranada(TEXT("/Script/Engine.SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));

	Explosao = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particula da Explosao"));
	Explosao->bAutoActivate = false;
	Explosao->bAutoDestroy = true;
	Explosao->SetRelativeScale3D(FVector(10.f, 10.f, 10.f));
	Explosao->SetupAttachment(MalhaDoAtor);
	ConstructorHelpers::FObjectFinder<UParticleSystem>ParticulaExplosao(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	if (Granada.Succeeded() && SomGranada.Succeeded() && ParticulaExplosao.Succeeded())
	{
		MalhaDoAtor->SetStaticMesh(Granada.Object);
		SomDaExplosao->SetSound(SomGranada.Object);
		Explosao->SetTemplate(ParticulaExplosao.Object);
	}


}

// Called when the game starts or when spawned
void AGranada::BeginPlay()
{
	Super::BeginPlay();
	MalhaDoAtor->SetSimulatePhysics(true);
	MalhaDoAtor->SetEnableGravity(true);
	GetWorldTimerManager().SetTimer(Temporizador, this, &AGranada::ExplodirGranada, 5.f, false);

	//TempoDevagar(0.1f);

}

// Called every frame
void AGranada::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGranada::ExplodirGranada()
{
	SetLifeSpan(5.5f);
	SomDaExplosao->Play();
	Explosao->ActivateSystem();
	MalhaDoAtor->SetVisibility(false);
	TempoDevagar(0.05f);
	ImpulsoRadial(500.f, 1000.f);
}

void AGranada::TempoDevagar(float DilatacaoDoTempo)
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DilatacaoDoTempo);
	GetWorldTimerManager().SetTimer(TimerDoTempo, this, &AGranada::RestaurarTempo, (3 * DilatacaoDoTempo), false);
}
void AGranada::RestaurarTempo()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	GetWorldTimerManager().ClearTimer(TimerDoTempo);
}

void AGranada::ImpulsoRadial(float Raio, float Forca)
{
	for (TActorIterator<AStaticMeshActor>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		UStaticMeshComponent* RaizDoStaticMesh;
		RaizDoStaticMesh = Cast<UStaticMeshComponent>(ActorItr->GetRootComponent());
		if (RaizDoStaticMesh)
		{
			if (RaizDoStaticMesh->Mobility == EComponentMobility::Movable)
			{
				RaizDoStaticMesh->SetSimulatePhysics(true);
				RaizDoStaticMesh->AddRadialImpulse(GetActorLocation(), Raio, Forca, ERadialImpulseFalloff::RIF_Linear, true);
			}
		}
	}
	for (TObjectIterator<USkeletalMeshComponent>It; It; ++It)
	{
		if (It->GetWorld() == GetWorld())
		{
			if (It->ComponentHasTag(FName("PlayerCPP")))
			{
				ACharacter* OutroInimigo = Cast<ACharacter>(It->GetOwner());
				UParticleSystemComponent* Particula = Cast<UParticleSystemComponent>(OutroInimigo->GetComponentByClass(UParticleSystemComponent::StaticClass()));

				It->SetSimulatePhysics(true);
				It->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				Particula->Activate(true);
				//It->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
				It->AddRadialImpulse(GetActorLocation(), Raio, Forca, ERadialImpulseFalloff::RIF_Linear, true);
			}
			
		}

	}
}
