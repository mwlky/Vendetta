#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::TryInteract(UCameraComponent* CameraComponent, bool Cancel, bool SecondInteraction)
{
	if (!CameraComponent)
	{
		return;
	}
	
	FRotator cameraRotation = CameraComponent->GetComponentRotation();
	FQuat cameraQuaternion = FQuat(cameraRotation);
	FVector forwardVector = cameraQuaternion.GetForwardVector();

	AActor* cameraOwner = CameraComponent->GetOwner();
	FVector location = cameraOwner->GetActorLocation();

	FVector start = location;
	FVector end = forwardVector * InteractionDistance + location;

	FHitResult hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.TraceTag = FName("InteractableTrace");
	
	if(GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_GameTraceChannel1, Params))
	{
		AInteractable* Interactable = Cast<AInteractable>(hit.GetActor());

		if (Interactable == nullptr)
		{
			return;
		}

		if (Cancel)
		{
			Interactable->CancelInteraction();
			return;
		}
		
		if (SecondInteraction)
			Interactable->AlternativeInteraction();
		
		else
			Interactable->MainInteraction();
	}
}



