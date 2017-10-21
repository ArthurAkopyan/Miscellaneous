// Fill out your copyright notice in the Description page of Project Settings.

#include "Museum290.h"
#include "ReplaceVolume.h"


// Sets default values
AReplaceVolume::AReplaceVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	RootComponent = Root;


	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyShape"));
	HitBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	HitBox->bGenerateOverlapEvents = true;
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AReplaceVolume::OnPlayerEnterBox);
}

// Called when the game starts or when spawned
void AReplaceVolume::BeginPlay()
{
	Super::BeginPlay();
	HitBox->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void AReplaceVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AReplaceVolume::OnPlayerEnterBox(UPrimitiveComponent* OverLapComp, AActor* OtherThing, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool FromSweep, const FHitResult& Sweep)
{
	if (OtherThing != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Replacing Volume Number: %d"), Debug);
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
		Destroy();
	}
}
