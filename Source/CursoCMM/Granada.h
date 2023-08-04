// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Granada.generated.h"

UCLASS()
class CURSOCMM_API AGranada : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGranada();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Properties
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MalhaDoAtor;

	UPROPERTY(EditAnywhere, Category = "Colisor")
	class USphereComponent* ColisorDoAtor;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class UAudioComponent* SomDaExplosao;

	UPROPERTY(EditAnywhere, Category = "Partícula")
	class UParticleSystemComponent* Explosao;

	FTimerHandle Temporizador, TimerDoTempo;

	//Functions
	UFUNCTION()
	void ExplodirGranada();

	UFUNCTION()
	void TempoDevagar(float DilatacaoDOTempo);

	UFUNCTION()
	void RestaurarTempo();

	UFUNCTION()
	void ImpulsoRadial(float Raio, float Forca);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
