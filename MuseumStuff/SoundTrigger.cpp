// Fill out your copyright notice in the Description page of Project Settings.

#include "Museum290.h"
#include "SoundTrigger.h"


// Sets default values
ASoundTrigger::ASoundTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	VolumeRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	RootComponent = VolumeRoot;


	VolumeHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyShape"));
	VolumeHitBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	VolumeHitBox->bGenerateOverlapEvents = true;
	VolumeHitBox->OnComponentBeginOverlap.AddDynamic(this, &ASoundTrigger::OnPlayerEnterBox);

}

// Called when the game starts or when spawned
void ASoundTrigger::BeginPlay()
{
	Super::BeginPlay();
	VolumeHitBox->AttachToComponent(VolumeRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void ASoundTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoundTrigger::OnPlayerEnterBox(UPrimitiveComponent* OverLapComp, AActor* OtherThing, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool FromSweep, const FHitResult& Sweep)
{
	UGameplayStatics::PlaySoundAtLocation(this, SoundFile, VolumeLocation);
	Destroy();
}
