// Damian Gorenski copyrights 2024


#include "SicilianPlayerController.h"

#include "Camera/CameraComponent.h"

void ASicilianPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	m_PlayerCharacter = Cast<APlayerCharacter>(PlayerCharacter);
}

void ASicilianPlayerController::SwitchCameraView(AActor* Actor, bool ShowCursor)
{
	SetViewTargetWithBlend(Actor, BlendTime, VTBlend_Linear);
	bShowMouseCursor = ShowCursor;
	bEnableClickEvents = ShowCursor;
	bEnableMouseOverEvents = ShowCursor;
	
	FTimerHandle Handle;
	m_PlayerCharacter->bIsBlending = true;
	m_PlayerCharacter->bIsInteracting = true;
	GetWorldTimerManager().SetTimer(Handle, this, &ASicilianPlayerController::IsBlendingSetFalse, BlendTime, false);
}

void ASicilianPlayerController::SwitchCameraToPlayerDefault()
{
	bShowMouseCursor = false;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	FTimerHandle InteractingHandle;
	FTimerHandle BlendingHandle;

	SetViewTargetWithBlend(m_PlayerCharacter, BlendTime, VTBlend_Linear);
	
	m_PlayerCharacter->bIsBlending = true;

	GetWorldTimerManager().SetTimer(InteractingHandle, this, &ASicilianPlayerController::IsInteractingSetFalse, BlendTime, false);
	GetWorldTimerManager().SetTimer(BlendingHandle, this, &ASicilianPlayerController::IsBlendingSetFalse, BlendTime, false);
}

void ASicilianPlayerController::IsBlendingSetFalse()
{
	m_PlayerCharacter->bIsBlending = false;
}

void ASicilianPlayerController::IsInteractingSetFalse()
{
	m_PlayerCharacter->bIsInteracting = false;

}


