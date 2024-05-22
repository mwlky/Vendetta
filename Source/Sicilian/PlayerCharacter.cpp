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

AInteractable* APlayerCharacter::RaycastForInteractable(UCameraComponent* CameraComponent)
{
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

		return Interactable;
	}
	
	return nullptr;
}

void APlayerCharacter::TryInteract(UCameraComponent* CameraComponent, bool Cancel, bool AlternativeInteraction)
{
	if (!CameraComponent)
		return;

	AInteractable* Interactable = RaycastForInteractable(CameraComponent);
	
	if (!Interactable)
		return;

	if (Cancel)
		Interactable->CancelInteraction();

	else if (AlternativeInteraction)
		Interactable->AlternativeInteraction();

	else
		Interactable->MainInteraction();
}



