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
	virtual void BeginPlay() override;
	void PutRequest();

public:
	virtual void MainInteraction() override;
	virtual void AlternativeInteraction() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	class ARequestManager* m_RequestsManager = nullptr;
	
};
