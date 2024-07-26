// Damian Gorenski copyrights 2024

#include "ARequestHolder.h"

#include "Requests/RequestsManager.h"

AARequestHolder::AARequestHolder()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AARequestHolder::BeginPlay()
{
	Super::BeginPlay();

	if (m_RequestsManager)
		m_RequestsManager->RequestPickedUp.AddDynamic(this, &AARequestHolder::HandleRequestPickedUp);
}

void AARequestHolder::PutRequest()
{
	m_RequestsManager->PutRequest();
	Highlight(false, true);
}

void AARequestHolder::HandleRequestPickedUp()
{
	Highlight(true, true);
}

void AARequestHolder::MainInteraction()
{
	PutRequest();
}

void AARequestHolder::AlternativeInteraction()
{
	PutRequest();
}
