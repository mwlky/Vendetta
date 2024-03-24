// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "InteractionSystem/Interactable.h"
#include "Sicilian/SicilianGameModeBase.h"
#include "RequestInteraction.generated.h"


UCLASS()
class SICILIAN_API ARequestInteraction : public AInteractable
{
	GENERATED_BODY()

	ARequestInteraction();

public:
	UPROPERTY(EditAnywhere)
	class ARequestManager* RequestsManager = nullptr; 
	
private:
	virtual void Interact() override;
	virtual void CancelInteraction() override;
	virtual void BeginPlay() override;
};
