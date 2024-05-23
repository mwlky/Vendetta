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
	AInteractable* RaycastForInteractable(class UCameraComponent* CameraComponent);

	UFUNCTION(BlueprintCallable)
	void TryInteract(class UCameraComponent* CameraComponent, bool Cancel, bool AlternativeInteraction);
	
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

	bool bPickedUpRequest = false;

	class AHudManager* m_HudManager = nullptr;
	class ASicillianPlayerController* m_PlayerController = nullptr;
	
	class UCameraComponent* m_Camera = nullptr;

private:
	UFUNCTION(BlueprintCallable, Category = "Dependency Injection")
	void InjectCamera(UCameraComponent* Camera);
};
