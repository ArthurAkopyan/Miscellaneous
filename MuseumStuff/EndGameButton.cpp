
#include "Museum290.h"
#include "EndGameButton.h"


// Sets default values
AEndGameButton::AEndGameButton()
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
void AEndGameButton::BeginPlay()
{
	Super::BeginPlay();
	MyMesh->AttachToComponent(PickUpRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	HitBox->AttachToComponent(PickUpRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void AEndGameButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEndGameButton::End()
{
	//UE_LOG(LogTemp, Warning, TEXT("Ending"));
	MyMesh->SetMaterial(0, Material);
	UE_LOG(LogTemp, Warning, TEXT("HitEnd"));
	AReplace* Stuff;
	if (WindowReplace != NULL)
	{
		AActor* Stuffer = WindowReplace;
		Stuff = Cast<AReplace>(Stuffer);
		Stuff->Replacer();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WindowReplace not initialized"));
	}
	UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, GetActorLocation() );
	GetWorld()->GetTimerManager().SetTimer(EndTimer, this, &AEndGameButton::Reset, 0.3f, false);
}
void AEndGameButton::Reset()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
