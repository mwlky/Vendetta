// Damian Gorenski copyrights 2024

#include "RequestInteraction.h"
#include "Requests/RequestsManager.h"

ARequestInteraction::ARequestInteraction()
{
}

void ARequestInteraction::SetNormalPosition()
{
	SetActorLocation(m_NormalPosition);
}

void ARequestInteraction::BeginPlay()
{
	Super::BeginPlay();
	
	RequestsManager->RequestGenerated.AddDynamic(this, &ARequestInteraction::HandleRequest);

	m_NormalPosition = GetActorLocation();
}

void ARequestInteraction::MainInteraction()
{
	RequestsManager->StartInteraction();
}

void ARequestInteraction::CancelInteraction()
{
	RequestsManager->CancelInteraction();
}

void ARequestInteraction::AlternativeInteraction()
{
	if(!RequestsManager->TryPickUpRequest())
		return;
	
	SetActorLocation(PickUpPosition);
}

void ARequestInteraction::HandleRequest(FRequest Request)
{
	SetNormalPosition();
}
