// Damian Gorenski copyrights 2024


#include "RequestInteraction.h"

#include "Requests/RequestsManager.h"

ARequestInteraction::ARequestInteraction()
{
	
}

void ARequestInteraction::BeginPlay()
{
}

void ARequestInteraction::Interact()
{
	RequestsManager->StartInteraction();
	// m_GameMode->StartInteraction(RequestCamera);
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));
}

void ARequestInteraction::CancelInteraction()
{
	RequestsManager->CancelInteraction();
}
