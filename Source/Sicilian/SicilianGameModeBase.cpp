// Fill out your copyright notice in the Description page of Project Settings.

#define DEBUG(x) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, x);

#include "SicilianGameModeBase.h"

#include "Camera/CameraActor.h"

void ASicilianGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	m_RequestManager = new RequestManager(RequestData);
}

void ASicilianGameModeBase::IsBlendingSetFalse()
{
	bIsDuringBlend = false;
}

void ASicilianGameModeBase::IsInteractingSetFalse()
{
	bIsInteracting = false;
}

void ASicilianGameModeBase::StartInteraction(ACameraActor* camera)
{
	if (bIsInteracting)
	{
		return;
	}
	
	if (!camera)
	{
		return;
	}

	const FRequest* Request = m_RequestManager->GenerateRequest();
	RequestGenerated.Broadcast(*Request);

	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	controller->SetViewTargetWithBlend(camera,BlendTime, VTBlend_Cubic);
	controller->bShowMouseCursor = true;
	controller->bEnableClickEvents = true;
	controller->bEnableMouseOverEvents = true;
	m_RequestManager->StartInteraction();
	InteractionStarted.Broadcast();
	
	FTimerHandle Handle;
	bIsDuringBlend = true;
	bIsInteracting = true;
	GetWorldTimerManager().SetTimer(Handle, this, &ASicilianGameModeBase::IsBlendingSetFalse, BlendTime, false);
}

void ASicilianGameModeBase::CancelInteraction()
{
	if (!bIsInteracting)
	{
		return;
	}

	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	controller->bShowMouseCursor = false;
	controller->bEnableClickEvents = false;
	controller->bEnableMouseOverEvents = false;
	controller->SetViewTargetWithBlend(GetWorld()->GetFirstPlayerController()->GetPawn(),
	                                                               BlendTime, VTBlend_Cubic);

	FTimerHandle InteractingHandle;
	FTimerHandle BlendingHandle;
	
	bIsDuringBlend = true;
	GetWorldTimerManager().SetTimer(InteractingHandle, this, &ASicilianGameModeBase::IsInteractingSetFalse, BlendTime, false);
	GetWorldTimerManager().SetTimer(BlendingHandle, this, &ASicilianGameModeBase::IsBlendingSetFalse, BlendTime, false);
	InteractionFinished.Broadcast();
}
