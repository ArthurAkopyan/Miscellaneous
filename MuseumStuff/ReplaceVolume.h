// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ReplaceVolume.generated.h"

UCLASS()
class MUSEUM290_API AReplaceVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AReplaceVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPlayerEnterBox(UPrimitiveComponent* OverLapComp, AActor* OtherThing, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool FromSweep, const FHitResult& Sweep);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Object1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Replacement1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Object2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Replacement2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Object3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Replacement3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float Debug = -1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//UAudioComponent Play;


	//Static Mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UShapeComponent* HitBox;

};