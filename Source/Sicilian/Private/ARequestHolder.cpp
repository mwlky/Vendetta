// Damian Gorenski copyrights 2024

#include "ARequestHolder.h"

AARequestHolder::AARequestHolder()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AARequestHolder::Activate()
{
	m_IsActive = true;
	Highlight(true, true);
}

void AARequestHolder::BeginPlay()
{
	Super::BeginPlay();
}

void AARequestHolder::PutRequest()
{
	if (!m_IsActive)
		return;

	m_IsActive = false;
	m_RequestsManager->PutRequest();
	Highlight(false, true);
}

void AARequestHolder::MainInteraction()
{
	PutRequest();
}

void AARequestHolder::AlternativeInteraction()
{
	PutRequest();
}
