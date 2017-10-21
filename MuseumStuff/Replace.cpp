// Fill out your copyright notice in the Description page of Project Settings.

#include "Museum290.h"
#include "Replace.h"


// Sets default values
AReplace::AReplace()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PickUpRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	RootComponent = PickUpRoot;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));


	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyShape"));
	HitBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

}

// Called when the game starts or when spawned
void AReplace::BeginPlay()
{
	Super::BeginPlay();
	lock = true;
	MyMesh->AttachToComponent(PickUpRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	HitBox->AttachToComponent(PickUpRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void AReplace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AReplace::Replacer()
{
	if (lock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Replace %d"), Debug);
		if (Object1 != NULL)
		{
			Replacement1->SetActorLocation(Object1->GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("Replacing1"));
			Object1->Destroy();
		}
		if (Object2 != NULL)
		{
			Replacement2->SetActorLocation(Object2->GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("Replacing2"));
			Object2->Destroy();
		}
		if (Object3 != NULL)
		{
			Replacement3->SetActorLocation(Object3->GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("Replacing3"));
			Object3->Destroy();
		}
		//UMaterialInterface* Bob = MyMesh->GetMaterial(0);
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
		MyMesh->SetMaterial(0, Material);
		lock = false;
		return true;
	}
	else
	{
		return false;
	}
}
