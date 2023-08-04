// Fill out your copyright notice in the Description page of Project Settings.


#include "MeuGameMode.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Granada.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "RayCastPlayerController.h"

AMeuGameMode::AMeuGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C'"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = ARayCastPlayerController::StaticClass();
	}
}

void AMeuGameMode::BeginPlay()
{
	Super::BeginPlay();
	/*TArray<AActor*>LocalGranadas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), LocalGranadas);
	
	if (LocalGranadas.Num() != 0)
	{
		FActorSpawnParameters params = FActorSpawnParameters();

		for (auto It : LocalGranadas)
		{
			GetWorld()->SpawnActor<AGranada>(It->GetActorLocation(), It->GetActorRotation(), params);
		}
	}*/
}
