// Fill out your copyright notice in the Description page of Project Settings.

#include "Museum290.h"
#include "Gravity.h"
#include "Replace.h"

// Sets default values
AGravity::AGravity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	RootComponent = Root;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyShape"));
	HitBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}

// Called when the game starts or when spawned
void AGravity::BeginPlay()
{
	Super::BeginPlay();
	MyMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	HitBox->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void AGravity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->GetTimerManager().GetTimerRemaining(Gravy) >= 0 && first)
	{
		FVector Translate = Ball->GetActorLocation() - FVector(0.0f, 0.0f, (1600 - 400 * (4 - GetWorld()->GetTimerManager().GetTimerRemaining(Gravy))) * DeltaTime);
		UE_LOG(LogTemp, Warning, TEXT("Time Remaining %f"), GetWorld()->GetTimerManager().GetTimerRemaining(Gravy));
		UE_LOG(LogTemp, Warning, TEXT("Gravity %f"), (1600 - 400 * (4 - GetWorld()->GetTimerManager().GetTimerRemaining(Gravy))) * DeltaTime);
		Ball->SetActorLocation(Translate);
		if (Ball->GetActorLocation().Z < LowerZ)
		{
			Ball->SetActorLocation(FVector(Ball->GetActorLocation().X, Ball->GetActorLocation().Y, UpperZ));
		}
	}
	else if (!first)
	{

	}
	else
	{
		FVector Translate = Ball->GetActorLocation() - FVector(0.0f, 0.0f, 900 * DeltaTime);
		Ball->SetActorLocation(Translate);
		if (Ball->GetActorLocation().Z < LowerZ)
		{
			Ball->SetActorLocation(FVector(Ball->GetActorLocation().X, Ball->GetActorLocation().Y, UpperZ));
		}
	}
}

void AGravity::Grav()
{
	if (lock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gravity"));
		GetWorld()->GetTimerManager().SetTimer(Gravy, this, &AGravity::Reset, 4.0f, false);
		lock = false;
	}
}

void AGravity::Reset()
{
	if (first)
	{
		GetWorld()->GetTimerManager().SetTimer(Gravy, this, &AGravity::Reset, 6.0f, false);
		first = false;
	}
	else
	{
		AReplace* Stuff;
		AActor* Stuffer = TeleporterDoor3;
		Stuff = Cast<AReplace>(Stuffer);
		Stuff->Replacer();
	}
}