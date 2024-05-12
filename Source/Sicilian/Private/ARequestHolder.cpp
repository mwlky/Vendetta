// Damian Gorenski copyrights 2024

#include "ARequestHolder.h"

#include "Requests/RequestsManager.h"

AARequestHolder::AARequestHolder()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Box;
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
	SetOutlineActivity(false);
}

void AARequestHolder::HandleRequestPickedUp()
{
	SetOutlineActivity(true);
}

void AARequestHolder::SetOutlineActivity(bool Activity)
{	
	Box->SetRenderCustomDepth(Activity);
}

void AARequestHolder::MainInteraction()
{
	PutRequest();
}

void AARequestHolder::AlternativeInteraction()
{
	PutRequest();
}
