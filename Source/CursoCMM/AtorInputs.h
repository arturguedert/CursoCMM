// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AtorInputs.generated.h"

UCLASS()
class CURSOCMM_API AAtorInputs : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAtorInputs();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Velocidade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float VelocidadeDeRotacao;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caracter")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UFUNCTION()
		void MoveVerticalmente(float eixoVertical);

	UFUNCTION()
		void MoveHorizontalmente(float eixoHorizontal);

	UFUNCTION()
		void RotacionaEmZ(float rotacaoZ);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

};
