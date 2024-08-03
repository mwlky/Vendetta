// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Requests/RequestsManager.h"
#include "InteractionSystem/Interactable.h"
#include "ARequestHolder.generated.h"

UCLASS()
class SICILIAN_API AARequestHolder : public AInteractable
{
	GENERATED_BODY()
	
public:	
	AARequestHolder();
	
public:
	void Activate();
	
	virtual void MainInteraction() override;
	virtual void AlternativeInteraction() override;

protected:
	void PutRequest();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Dependencies")
	class ARequestManager* m_RequestsManager = nullptr;

	bool m_IsActive = false;
};
