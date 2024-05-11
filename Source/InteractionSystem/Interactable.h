#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class INTERACTIONSYSTEM_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractable();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void MainInteraction();

	UFUNCTION(BlueprintCallable)
	virtual void AlternativeInteraction();

	UFUNCTION(BlueprintCallable)
	virtual void CancelInteraction();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* m_Mesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* m_BoxComponent = nullptr;
};
