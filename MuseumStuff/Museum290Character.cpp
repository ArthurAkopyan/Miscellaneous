// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Museum290.h"
#include "Museum290Character.h"
#include "Museum290Projectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "String.h"
#include "DrawDebugHelpers.h"
#include "Replace.h"
#include "Deleter.h"
#include "Gravity.h"
#include "EndGameButton.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AMuseum290Character

AMuseum290Character::AMuseum290Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	zoomer = 0.0f;
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-40.0f, 1.75f, 45.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->Hand = EControllerHand::Right;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

																				// Uncomment the following line to turn motion controllers on by default:
																				//bUsingMotionControllers = true;
}

void AMuseum290Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = 700.0f;

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
}

/////////////
// Input

void AMuseum290Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMuseum290Character::TouchStarted);
	if (EnableTouchscreenMovement(PlayerInputComponent) == false)
	{
		//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMuseum290Character::OnFire);
	}

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMuseum290Character::OnResetVR);


	PlayerInputComponent->BindAxis("MoveForward", this, &AMuseum290Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMuseum290Character::MoveRight);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	PlayerInputComponent->BindAction("RayCast", IE_Pressed, this, &AMuseum290Character::RayCast);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AMuseum290Character::Zoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AMuseum290Character::StopZoom);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//PlayerInputComponent->BindAction("CameraShake", IE_Pressed, this, &AMuseum290Character::CameraShake);
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMuseum290Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMuseum290Character::LookUpAtRate);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AMuseum290Character::RayCast()
{
	//Safty bool
	bool Result = true;
	FHitResult* HitResult = new FHitResult();
	FVector CameraForward = GetControlRotation().Vector();
	FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation(); //+ FVector(0,0,30); 
	FVector EndTrace = StartTrace + CameraForward * 230;
	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 1.f, 0, 3);
	if (Result)
	{

		FCollisionQueryParams* CQP = new FCollisionQueryParams();
		//Can use LineTraceMulti...etc
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *CQP))
		{
			if (HitResult->GetActor() != NULL)
			{
				//Use the Resulting actor to do something
				//Right Now it deletes what ever you click on
				if (HitResult->GetActor()->ActorHasTag("Replace") && PaintingReplace)
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit"));
					AReplace* Stuff;
					AActor* Stuffer = HitResult->GetActor();
					Stuff = Cast<AReplace>(Stuffer);
					if (Stuff->Replacer())
					{
						PaintingCounter++;
						UE_LOG(LogTemp, Warning, TEXT("Replacement Clicks Done%d"), PaintingCounter);
					}
					if (PaintingCounter == 2)
					{
						UGameplayStatics::PlaySoundAtLocation(this, Painting3Sound, Painting3SoundLocation);
						GetWorld()->GetTimerManager().SetTimer(Del, this, &AMuseum290Character::Reset, 18.0f, false);
						PaintingReplace = false;
					}
					if (PaintingCounter == 10 && tenLock)
					{
						UGameplayStatics::PlaySoundAtLocation(this, Painting10Sound, Painting10SoundLocation);
						GetWorld()->GetTimerManager().SetTimer(Del, this, &AMuseum290Character::Reset, 17.0f, false);
						tenLock = false;
					}
					//Stuff = (AReplace)(Stuffer);//->GetDefaultSubobjects(Replaced);
				}
				else if (HitResult->GetActor()->ActorHasTag("Delete"))
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit"));
					ADeleter* Stuff;
					AActor* Stuffer = HitResult->GetActor();
					Stuff = Cast<ADeleter>(Stuffer);
					Stuff->Deletered();
				}
				// ADD THIS SHIT
				//////////////////////////////////////////////////////////////////////////////////////////
				else if (HitResult->GetActor()->ActorHasTag("Walrus") && !Walrus)
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit"));
					ADeleter* Stuff;
					AActor* Stuffer = HitResult->GetActor();
					Stuff = Cast<ADeleter>(Stuffer);
					Stuff->Deletered();
					GetWorld()->GetTimerManager().SetTimer(Del, this, &AMuseum290Character::Reset, 0.5f, false);
					Walrus = true;
				}
				else if (HitResult->GetActor()->ActorHasTag("Key1") && !KeyOne)
				{
					UE_LOG(LogTemp, Warning, TEXT("Key1"));
					AReplace* Stuff = NULL;
					if (Key1Replace != NULL)
					{
						AActor* Stuffer = Key1Replace;
						Stuff = Cast<AReplace>(Stuffer);
						Stuff->Replacer();
						HitResult->GetActor()->Destroy();
						KeyOne = true;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Key2Replace is not initialized"));
					}
				}
				else if (HitResult->GetActor()->ActorHasTag("Key2") && !KeyTwo)
				{
					UE_LOG(LogTemp, Warning, TEXT("Key2"));
					AReplace* Stuff;
					if (Key2Replace != NULL)
					{
						AActor* Stuffer = Key2Replace;
						Stuff = Cast<AReplace>(Stuffer);
						Stuff->Replacer();
						HitResult->GetActor()->Destroy();
						KeyTwo = true;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Key2Replace is not initialized"));
					}
				}
				else if (HitResult->GetActor()->ActorHasTag("Gravity") && gravlock)
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit"));
					AGravity* Stuff;
					AActor* Stuffer = HitResult->GetActor();
					Stuff = Cast<AGravity>(Stuffer);
					Stuff->Grav();
					GetCharacterMovement()->GravityScale = 0.2f;
					GetCharacterMovement()->MaxWalkSpeed = 300.0f;
					gravlock = false;
				}
				else if (HitResult->GetActor()->ActorHasTag("End"))
				{
					UE_LOG(LogTemp, Warning, TEXT("End"));
					AEndGameButton* Stuff;
					AActor* Stuffer = HitResult->GetActor();
					Stuff = Cast<AEndGameButton>(Stuffer);
					Stuff->End();
				}
				//////////////////////////////////////////////////////////////////////////////////////////

				//HitResult->GetActor()->Destroy();
			}
			//if(HitResult->GetComponent.is//UStaticMeshComponent)
		}
	}
}
// ADD THIS SHIT
//////////////////////////////////////////////////////////////////////////////////////////////
void AMuseum290Character::Reset()
{
	if (PaintingCounter == 2)
	{
		AReplace* Stuff2;
		AActor* Stuffer2 = TeleportRoomDoorReplace1;
		Stuff2 = Cast<AReplace>(Stuffer2);
		Stuff2->Replacer();
	}
	else if (PaintingCounter == 10)
	{
		AReplace* Stuff2;
		AActor* Stuffer2 = TeleportRoomDoorReplace2;
		Stuff2 = Cast<AReplace>(Stuffer2);
		Stuff2->Replacer();
	}
	else if (Temp2)
	{
		AReplace* Stuff;
		AActor* Stuffer = WalrusReplace;
		Stuff = Cast<AReplace>(Stuffer);
		Stuff->Replacer();
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, WalrusSound, WalrusSoundLocation);
		GetWorld()->GetTimerManager().SetTimer(Del, this, &AMuseum290Character::Reset, 14.0f, false);
		Temp2 = true;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
void AMuseum290Character::Zoom()
{
	Aimer = true;
	UE_LOG(LogTemp, Warning, TEXT("True"));
}
void AMuseum290Character::StopZoom()
{
	UE_LOG(LogTemp, Warning, TEXT("False"));
	Aimer = false;
}
void AMuseum290Character::Tick(float DeltaTime)
{
	//&& FirstPersonCameraComponent->GetComponentLocation().X >= -39
	if (Aimer)
	{
		//FirstPersonCameraComponent->FieldOfView

		//UE_LOG(LogTemp, Warning, TEXT("RotationalValue %f"), FirstPersonCameraComponent->GetRelativeTransform().GetRotation().Y);
		//FVector Translate = FVector(1000.0f * DeltaTime, 0.0f, 0.0f);
		//Translate = Translate + FirstPersonCameraComponent->GetRelativeTransform().GetLocation();
		//FirstPersonCameraComponent->SetRelativeLocation(Translate);

		zoomer += 1000.0f * DeltaTime;
		//UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Camera Transform Position is %s"), *(Translate).ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Aim1"));
		//FirstPersonCameraComponent->GetRelativeTransform().GetLocation().X

		if (zoomer >= 60.0f)
		{
			zoomer = 60.0f;
			//FirstPersonCameraComponent->SetRelativeLocation(FVector(10.0f, 1.75f, 64.f));
		}
	}
	else if (!Aimer)
	{
		//FVector Translate = FVector(-1000.0f * DeltaTime, 0.0f, 0.0f);
		//Translate = Translate + FirstPersonCameraComponent->GetRelativeTransform().GetLocation();
		//FirstPersonCameraComponent->SetRelativeLocation(Translate);

		zoomer -= 1000.0f * DeltaTime;


		if (zoomer <= 0)
		{
			zoomer = 0.0f;
			//GetCharacterMovement()->MaxWalkSpeed = 400.0f;
			//
			//FirstPersonCameraComponent->SetRelativeLocation(FVector(-40.0f, 1.75f, 64.f));
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("RotationalValue %f"), FirstPersonCameraComponent->FieldOfView);
	FVector Translate = FVector(zoomer * FMath::Cos(FMath::Abs(2.2 * FirstPersonCameraComponent->GetRelativeTransform().GetRotation().Y)), 0.0f, zoomer * FMath::Sin(-2.2 * FirstPersonCameraComponent->GetRelativeTransform().GetRotation().Y));
	//UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Camera Transform Position is %s"), *(Translate).ToString());
	FirstPersonCameraComponent->FieldOfView = 90 - zoomer / 2;
	Translate = Translate + FVector(-40.0f, 1.75f, 45.f);
	FirstPersonCameraComponent->SetRelativeLocation(Translate);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void AMuseum290Character::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			if (bUsingMotionControllers)
			{
				const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
				const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
				World->SpawnActor<AMuseum290Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}
			else
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<AMuseum290Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AMuseum290Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMuseum290Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AMuseum290Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AMuseum290Character::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AMuseum290Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMuseum290Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMuseum290Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMuseum290Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AMuseum290Character::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMuseum290Character::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AMuseum290Character::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMuseum290Character::TouchUpdate);
	}
	return bResult;
}