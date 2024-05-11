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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dependencies")
	class ARequestManager* RequestsManager = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Data")
	FVector PickUpPosition;

	void SetNormalPosition();
	
private:
	virtual void BeginPlay() override;
	virtual void MainInteraction() override;
	virtual void CancelInteraction() override;
	virtual void AlternativeInteraction() override;

	UFUNCTION()
	void HandleRequest(struct FRequest Request);

	FVector m_NormalPosition = FVector::Zero();
};
