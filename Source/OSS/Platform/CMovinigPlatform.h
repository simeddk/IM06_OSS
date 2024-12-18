#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CMovinigPlatform.generated.h"

UCLASS()
class OSS_API ACMovinigPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ACMovinigPlatform();

	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, Category = "Moving")
		float Speed;
};

