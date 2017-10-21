// Fill out your copyright notice in the Description page of Project Settings.

#include "Museum290.h"
#include "Deleter.h"


// Sets default values
ADeleter::ADeleter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	RootComponent = Root;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyShape"));
	HitBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}

// Called when the game starts or when spawned
void ADeleter::BeginPlay()
{
	Super::BeginPlay();
	lock = true;
	MyMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	HitBox->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void ADeleter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeleter::Deletered()
{
	if (lock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Delete %d"), Debug);
		if (Object != NULL)
		{
			Object->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Deleting1"));
		}
		if (Object2 != NULL)
		{
			Object2->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Deleting2"));
		}
		if (Object3 != NULL)
		{
			Object3->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Deleting3"));
		}
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
		MyMesh->SetMaterial(0, Material);
		lock = false;
	}
}
