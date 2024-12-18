#include "CMovinigPlatform.h"

ACMovinigPlatform::ACMovinigPlatform()
{
	Speed = 200.f;

	SetMobility(EComponentMobility::Movable);

	//Todo. Enable Tick ¤Ð¤Ð
}

void ACMovinigPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += FVector::RightVector * Speed * DeltaTime;

	SetActorLocation(CurrentLocation);
}