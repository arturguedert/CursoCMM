// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RayCastPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CURSOCMM_API ARayCastPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	virtual void SetupInputComponent() override;

	void AtirarRayCast();

	virtual void Tick(float DeltaTime) override;



protected:
	UPROPERTY()
		FVector LocalizacaoPontoDeVisaoDoPlayer;

	UPROPERTY()
		FRotator RotacaoPontoDeVisaoDoPlayer;

	
};
