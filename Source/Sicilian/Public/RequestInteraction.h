// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "InteractionSystem/Interactable.h"
#include "Sicilian/SicilianGameModeBase.h"
#include "RequestInteraction.generated.h"

/**
 * 
 */
UCLASS()
class SICILIAN_API ARequestInteraction : public AInteractable
{
	GENERATED_BODY()

	ARequestInteraction();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACameraActor* RequestCamera = nullptr;
	
private:
	void Interact() override;
	void CancelInteraction() override;
	void BeginPlay() override;
	
	ASicilianGameModeBase* m_GameMode = nullptr;
};
