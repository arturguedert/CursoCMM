// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerEsferico.h"
#include "Engine/Engine.h"

void ATriggerEsferico::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ATriggerEsferico::ColisaoDetectada);
	OnActorEndOverlap.AddDynamic(this, & ATriggerEsferico::DeixouDeColidir);

}

void ATriggerEsferico::ColisaoDetectada(AActor* me, AActor* other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Comecou a sobrepor em %s"), *other->GetActorLocation().ToString()));
	//other->Destroy();
}

void ATriggerEsferico::DeixouDeColidir(AActor* me, AActor* other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Deixou de sobrepor em %s"), *other->GetActorLocation().ToString()));
}
