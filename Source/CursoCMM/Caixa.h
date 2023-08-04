// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Caixa.generated.h"

UCLASS()
class CURSOCMM_API ACaixa : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACaixa();

	bool bDeuHit = false;
	FTimerHandle Delay;

	UPROPERTY(VisibleAnywhere, Category = "Caixa")
		class UBoxComponent* Colisor;

	UPROPERTY(EditAnywhere, Category = "Caixa")
		class UStaticMeshComponent* MalhaDaCaixa;

	UPROPERTY(EditAnywhere, Category = "Caixa")
		class UAudioComponent* SomDoHit;

	UPROPERTY(EditAnywhere, Category = "Caixa")
		class UParticleSystemComponent* ParticulaHit;

	UFUNCTION()
		void OcorreuHitNoComponente(UPrimitiveComponent* HitComponent, AActor* OtheActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OcorreuHitNoAtor(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool SelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
		void ResetExplosao();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
