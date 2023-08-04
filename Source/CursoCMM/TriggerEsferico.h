// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "TriggerEsferico.generated.h"

/**
 * 
 */
UCLASS()
class CURSOCMM_API ATriggerEsferico : public ATriggerSphere
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void ColisaoDetectada(AActor* me, AActor* other);

	UFUNCTION()
	void DeixouDeColidir(AActor* me, AActor* other);


public:
	virtual void BeginPlay() override;

};



