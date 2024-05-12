// Damian Gorenski copyrights 2024

#include "ARequestHolder.h"

#include "Requests/RequestsManager.h"

AARequestHolder::AARequestHolder()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AARequestHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARequestHolder::PutRequest()
{
	m_RequestsManager->PutRequest();
}

void AARequestHolder::MainInteraction()
{
	PutRequest();
}

void AARequestHolder::AlternativeInteraction()
{
	PutRequest();
}

void AARequestHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

