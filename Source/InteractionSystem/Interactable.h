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

	UPROPERTY(BlueprintReadWrite)
	class UStaticMeshComponent* MeshToHighlight = nullptr;
	
public:
	virtual void Highlight(bool bActive, bool bForce = false);
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void MainInteraction();

	UFUNCTION(BlueprintCallable)
	virtual void AlternativeInteraction();

	UFUNCTION(BlueprintCallable)
	virtual void CancelInteraction();

	virtual UTexture2D* GetIcon() const;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactable Components")
	class UBoxComponent* m_BoxComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactable Components")
	class UStaticMeshComponent* m_Mesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactable Settings")
	bool bHighlightable = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactable Settings")
	bool bIsInteractable = true;

private:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interactable Settings", meta = (AllowPrivateAccess = "true"))
	UTexture2D* m_InteractableIcon = nullptr;
};
