#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = Cast<USceneComponent>(GetCapsuleComponent());
	
	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_CameraComponent->SetupAttachment(SceneComponent);
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

void APlayerCharacter::TryInteract(UCameraComponent* CameraComponent, bool Cancel)
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

	FHitResult OutHit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.TraceTag = FName("InteractableTrace");
	
	if(GetWorld()->LineTraceSingleByChannel(OutHit, start, end, ECC_GameTraceChannel1, Params))
	{
		AInteractable* Interactable = Cast<AInteractable>(OutHit.GetActor());

		if (Interactable == nullptr)
			return;

		if (Cancel)
		{
			Interactable->CancelInteraction();
			return;
		}

		Interactable->Interact();
		
		m_CurrentInteractable = Interactable;
	}
}

void APlayerCharacter::CancelInteraction() const
{
	if (m_CurrentInteractable == nullptr)
		return;

	m_CurrentInteractable->CancelInteraction();
}