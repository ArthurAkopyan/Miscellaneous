// Fill out your copyright notice in the Description page of Project Settings.

#include "Museum290.h"
#include "Rest.h"
#include "Museum290Character.h"

// Sets default values
ARest::ARest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	RootComponent = Root;


	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyShape"));
	HitBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	HitBox->bGenerateOverlapEvents = true;
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ARest::OnPlayerEnterBox);

}

// Called when the game starts or when spawned
void ARest::BeginPlay()
{
	Super::BeginPlay();
	HitBox->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void ARest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ARest::OnPlayerEnterBox(UPrimitiveComponent* OverLapComp, AActor* OtherThing, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool FromSweep, const FHitResult& Sweep)
{
	AMuseum290Character* Stuff;
	AActor* Stuffer = OtherThing;
	Stuff = Cast<AMuseum290Character>(Stuffer);
	if (Stuff != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Resting Code"));
		Stuff->PaintingReplace = true;
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error Casting Player"));
	}

}
