// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SicillianPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SICILIAN_API ASicillianPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	bool bCanInteract = false;

private:
	virtual void Tick(float DeltaSeconds) override;

	void CheckInteraction();
};
