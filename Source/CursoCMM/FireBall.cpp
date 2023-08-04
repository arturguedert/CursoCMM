// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"


// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TempoDeExecucao = 0.f;
	AlturaDelta = 0.f;
	NovaLocalizacao = FVector(0.f, 0.f, 0.f);

	EsferaDeColisao = CreateDefaultSubobject<USphereComponent>(TEXT("Raiz"));
	EsferaDeColisao->InitSphereRadius(100.f);
	EsferaDeColisao->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = EsferaDeColisao;
	
	EsferaVisivel = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Esfera"));
	EsferaVisivel->SetupAttachment(RootComponent);
	
	ParticulaDeFogo = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticulaFogo"));
	ParticulaDeFogo->SetupAttachment(EsferaVisivel);
	ParticulaDeFogo->bAutoActivate = true;

	TextoDeExibicao = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Texto"));
	TextoDeExibicao->SetupAttachment(EsferaVisivel);
	TextoDeExibicao->SetRelativeLocation(FVector(0.f, 0.f, 110.f));
	TextoDeExibicao->SetHorizontalAlignment(EHTA_Center);
	TextoDeExibicao->SetYScale(1.f);
	TextoDeExibicao->SetXScale(1.f);
	TextoDeExibicao->SetText(FText::FromString("C++ na Unreal"));
	TextoDeExibicao->SetTextRenderColor(FColor::Red);
	TextoDeExibicao->SetVisibility(true);


	//Set the default StaticMesh, Material and Particle System for the Actor
	ConstructorHelpers::FObjectFinder<UStaticMesh>Esfera(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	ConstructorHelpers::FObjectFinder<UMaterialInterface>Material(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem>Particula(TEXT("/ Script / Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));

	
	if (Esfera.Succeeded() && Material.Succeeded() && Particula.Succeeded())
	{
		EsferaVisivel->SetStaticMesh(Esfera.Object);
		EsferaVisivel->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		EsferaVisivel->SetMaterial(0, Material.Object);
		ParticulaDeFogo->SetTemplate(Particula.Object);

	}

	OnActorBeginOverlap.AddDynamic(this, &AFireBall::IniciouSobreposicao);


}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NovaLocalizacao = this->GetActorLocation();
	AlturaDelta = FMath::Sin(TempoDeExecucao + DeltaTime) - FMath::Sin(TempoDeExecucao);
	NovaLocalizacao.Z += AlturaDelta * 20.f;
	TempoDeExecucao += DeltaTime;
	this->SetActorLocation(NovaLocalizacao);
	UE_LOG(LogTemp, Warning, TEXT("NovaLocalizacao = % s"), *NovaLocalizacao.ToString());

}

void AFireBall::IniciouSobreposicao(AActor* OverlappedActor, AActor* OtherActor)
{
	FString StringDeSaida;
	StringDeSaida = "Sobrepondo " + OtherActor->GetName();
	TextoDeExibicao->SetText(FText::FromString(StringDeSaida));

}
