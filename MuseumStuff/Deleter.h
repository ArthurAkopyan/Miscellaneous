// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Deleter.generated.h"

UCLASS()
class MUSEUM290_API ADeleter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADeleter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Object2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* Object3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int Debug;

	void Deletered();

	//Static Mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UShapeComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UMaterialInterface* Material;
private:

	bool lock;

};