// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EndGameButton.generated.h"

UCLASS()
class MUSEUM290_API AEndGameButton : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "Replace")
		TSubclassOf<class AReplace> Replaced;
public:
	// Sets default values for this actor's properties
	AEndGameButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void End();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* PickUpRoot;

	UPROPERTY(EditAnywhere)
		UShapeComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* WindowReplace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* ButtonSound;

	FTimerHandle EndTimer;

	void Reset();
};