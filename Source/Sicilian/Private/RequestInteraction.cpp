// Damian Gorenski copyrights 2024


#include "RequestInteraction.h"

ARequestInteraction::ARequestInteraction()
{
	
}

void ARequestInteraction::BeginPlay()
{
	m_GameMode = Cast<ASicilianGameModeBase>(GetWorld()->GetAuthGameMode());
}

void ARequestInteraction::Interact()
{
	m_GameMode->StartInteraction(RequestCamera);
	UE_LOG(LogTemp, Warning, TEXT("Int"));
}

void ARequestInteraction::CancelInteraction()
{
	m_GameMode->CancelInteraction();
}
