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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void IncreaseActiveCount();
	void DecreaseActiveCount();

private:
	UPROPERTY(EditAnywhere, Category = "Moving")
	int32 ActiveCount;

	UPROPERTY(EditAnywhere, Category = "Moving")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Moving", meta = (MakeEditWidget))
	FVector TargetLS;

private:
	FVector StartWS;
	FVector TargetWS;
};

