#include "PlayerCharacter.h"

#include "HudManager.h"
#include "SicillianPlayerController.h"

#include "Kismet/GameplayStatics.h"

#define DEBUG(x) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, x);

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	m_HudManager = Cast<AHudManager>(PlayerController->GetHUD());
	m_PlayerController = Cast<ASicillianPlayerController>(PlayerController);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_HudManager)
		return;

	if (!m_Camera)
		return;

	AInteractable* Interactable = RaycastForInteractable(m_Camera);

	if (Interactable)
	{
		m_HudManager->ShowInteractableDot(true);
		Interactable->Highlight(true);
		m_LastInteractable = Interactable;
	}
	else
	{
		m_HudManager->ShowBasicDot(true);
		if (!m_LastInteractable)
			return;

		m_LastInteractable->Highlight(false);
		m_LastInteractable = nullptr;
	}
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

	FVector location = CameraComponent->GetComponentLocation();

	FVector start = location;
	FVector end = forwardVector * InteractionDistance + location;

	FHitResult hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.TraceTag = FName("InteractableTrace");
	
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_GameTraceChannel1, Params))
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

void APlayerCharacter::InjectCamera(UCameraComponent* Camera)
{
	m_Camera = Camera;
}
