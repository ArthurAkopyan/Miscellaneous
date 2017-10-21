// Fill out your copyright notice in the Description page of Project Settings.

#include "Museum290.h"
#include "Teleport.h"


// Sets default values
ATeleport::ATeleport()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TeleportRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	RootComponent = TeleportRoot;


	TeleportHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyShape"));
	TeleportHitBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	TeleportHitBox->bGenerateOverlapEvents = true;
	TeleportHitBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleport::OnPlayerEnterBox);
	
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
	TeleportHitBox->AttachToComponent(TeleportRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleport::OnPlayerEnterBox(UPrimitiveComponent* OverLapComp, AActor* OtherThing, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool FromSweep, const FHitResult& Sweep)
{
	UGameplayStatics::PlaySoundAtLocation(this, TeleportSound, GetActorLocation());
	GetWorld()->GetTimerManager().SetTimer(Delay, this, &ATeleport::Reset, 0.5f, false);
	Holder = OtherThing;
	UE_LOG(LogTemp, Warning, TEXT("Teleporting"));
}

void ATeleport::Reset()
{
	UGameplayStatics::PlaySoundAtLocation(this, SoundFile, TeleportLocation);
	Holder->SetActorLocation(TeleportLocation);
}