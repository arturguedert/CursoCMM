// Fill out your copyright notice in the Description page of Project Settings.


#include "RayCastPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"

void ARayCastPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAction("Atirar", EInputEvent::IE_Released, this, &ARayCastPlayerController::AtirarRayCast);

}

void ARayCastPlayerController::AtirarRayCast()
{
	float Tamanho = 10000.f;
	//FVector Direcao = PlayerCameraManager->GetActorForwardVector();
	//FVector Origem = PlayerCameraManager->GetCameraLocation();
	FVector Direcao = RotacaoPontoDeVisaoDoPlayer.Vector();
	FVector Origem = LocalizacaoPontoDeVisaoDoPlayer;
	FVector PontoFinal = Origem + (Direcao * Tamanho);
	FHitResult ResultadoDoHit;
	FCollisionQueryParams CollisionParams;
	//bool ColidiuComAlgo = GetWorld()->LineTraceSingleByChannel(ResultadoDoHit, Origem, PontoFinal, ECollisionChannel::ECC_Camera, CollisionParams);
	bool ColidiuComAlgo = GetWorld()->LineTraceSingleByChannel(ResultadoDoHit, Origem, PontoFinal, ECollisionChannel::ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), Origem, PontoFinal, FColor::Red, false, 10.f, (uint8)0, 5.f);

	if (ColidiuComAlgo)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, (FName("Ator %s"), *ResultadoDoHit.GetActor()->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, (FName("Em %s"), *ResultadoDoHit.Location.ToString()));
	}
}

void ARayCastPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(LocalizacaoPontoDeVisaoDoPlayer, RotacaoPontoDeVisaoDoPlayer);

}
