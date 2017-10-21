// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Replace.generated.h"

UCLASS()
class MUSEUM290_API AReplace : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AReplace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
		int Debug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector ReplacementPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UMaterialInterface* Material;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//UAudioComponent Play;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* Sound;

	bool Replacer();

	//Static Mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* PickUpRoot;

	UPROPERTY(EditAnywhere)
		UShapeComponent* HitBox;

private:

	bool lock;

};
