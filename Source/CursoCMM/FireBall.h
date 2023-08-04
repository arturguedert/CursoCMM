// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireBall.generated.h"

UCLASS()
class CURSOCMM_API AFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Posição")
	float AlturaDelta;

	UPROPERTY(EditAnywhere, Category = "Posição")
	FVector NovaLocalizacao;

	UPROPERTY(EditAnywhere, Category = "Tempo")
	float TempoDeExecucao;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	UStaticMeshComponent* EsferaVisivel;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	class USphereComponent* EsferaDeColisao;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	UParticleSystemComponent* ParticulaDeFogo;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	class UTextRenderComponent* TextoDeExibicao;
	
	UFUNCTION()
	void IniciouSobreposicao(AActor* OverlappedActor, AActor* OtherActor);

};
