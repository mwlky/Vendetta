#include "Interactable.h"

#include "Components/BoxComponent.h"


AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
	
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Mesh->Mobility = EComponentMobility::Movable;
	RootComponent = m_Mesh;

	m_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collider"));
	m_BoxComponent->SetupAttachment(RootComponent);

	if (m_BoxComponent)
	{
		m_BoxComponent->SetCollisionObjectType(ECC_GameTraceChannel1); // Set collision channel
		m_BoxComponent->SetCollisionResponseToAllChannels(ECR_Block); // Block all channels
		m_BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); // Ignore pawn channel
	}
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractable::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Base interaction"));
}

void AInteractable::CancelInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("Canceling base interaction"));
}
