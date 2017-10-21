// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Rest.generated.h"

UCLASS()
class MUSEUM290_API ARest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARest();

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		TSubclassOf<class AMuseum290Character> Charactered;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPlayerEnterBox(UPrimitiveComponent* OverLapComp, AActor* OtherThing, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool FromSweep, const FHitResult& Sweep);

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UShapeComponent* HitBox;
	
};
