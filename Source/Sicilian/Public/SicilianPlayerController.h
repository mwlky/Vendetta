// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Sicilian/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "SicilianPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SICILIAN_API ASicilianPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SwitchCameraView(AActor*, bool);
	void SwitchCameraToPlayerDefault();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Request", meta = (AllowPrivateAccess = "true"))
	float BlendTime = 1.f;
	
	void IsBlendingSetFalse();
	void IsInteractingSetFalse();

	bool bIsBlending = false;
	bool bIsInteracting = false;

	APlayerCharacter* m_PlayerCharacter = nullptr;
};
