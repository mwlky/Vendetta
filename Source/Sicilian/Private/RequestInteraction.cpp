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
}

void ARequestInteraction::CancelInteraction()
{
	RequestsManager->CancelInteraction();
}
