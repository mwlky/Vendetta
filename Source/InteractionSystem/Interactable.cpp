#include "Interactable.h"

#include "Components/BoxComponent.h"


AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
	
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
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

void AInteractable::Highlight(bool bActive, bool bForce)
{
	if(!bHighlightable || !bForce)
		return;
	
	if(!MeshToHighlight)
		return;

	if(MeshToHighlight->bRenderCustomDepth == bActive)
		return;
	
	MeshToHighlight->SetRenderCustomDepth(bActive);
}

void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractable::MainInteraction()
{
}

void AInteractable::AlternativeInteraction()
{
}

void AInteractable::CancelInteraction()
{
}

UTexture2D* AInteractable::GetIcon() const
{
	return m_InteractableIcon;
}
