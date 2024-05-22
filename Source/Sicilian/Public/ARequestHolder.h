// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionSystem/Interactable.h"
#include "ARequestHolder.generated.h"

UCLASS()
class SICILIAN_API AARequestHolder : public AInteractable
{
	GENERATED_BODY()
	
public:	
	AARequestHolder();

protected:
	void PutRequest();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleRequestPickedUp();

public:
	void SetOutlineActivity(bool Activity);
	
	virtual void MainInteraction() override;
	virtual void AlternativeInteraction() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Box = nullptr;

private:
	
	UPROPERTY(EditAnywhere, Category = "Dependencies")
	class ARequestManager* m_RequestsManager = nullptr;
};