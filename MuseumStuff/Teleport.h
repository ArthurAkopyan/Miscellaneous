// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Teleport.generated.h"

UCLASS()
class MUSEUM290_API ATeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPlayerEnterBox(UPrimitiveComponent* OverLapComp, AActor* OtherThing, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool FromSweep, const FHitResult& Sweep);

	UPROPERTY(EditAnywhere)
		USceneComponent* TeleportRoot;

	UPROPERTY(EditAnywhere)
		UShapeComponent* TeleportHitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector TeleportLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* TeleportSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* SoundFile;

	FTimerHandle Delay;

	void Reset();

	AActor* Holder;
	
};
