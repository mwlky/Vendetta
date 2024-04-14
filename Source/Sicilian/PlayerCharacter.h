// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "InteractionSystem/Interactable.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class SICILIAN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void TryInteract(class UCameraComponent* CameraComponent, bool Cancel);

	void CancelInteraction() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseSpeed;

	UPROPERTY(EditAnywhere)
	float InteractionDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDuringRequest;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInteracting = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsBlending = false;

	UCameraComponent* GetCamera() const { return m_CameraComponent; }

private:
	AInteractable* m_CurrentInteractable = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
	class UCameraComponent* m_CameraComponent = nullptr;
};
