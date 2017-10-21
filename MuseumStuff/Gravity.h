// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Gravity.generated.h"

UCLASS()
class MUSEUM290_API AGravity : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Replace")
	TSubclassOf<class AReplace> Replaced;

public:
	// Sets default values for this actor's properties
	AGravity();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Ball;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* TeleporterDoor3;

	void Grav();

	bool lock = true;

	bool first = true;

	FTimerHandle Gravy;

	void Reset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* ButtonSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FrankieTalking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float UpperZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float LowerZ;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UShapeComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UMaterialInterface* Material;

	AActor* Character;

};
