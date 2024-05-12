// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Requests/FRequest.h"
#include "Requests/RequestsData.h"
#include "Sicilian/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "RequestsManager.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStarted);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFinished);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestGenerated, FRequest, Request);

UCLASS()
class REQUESTSYSTEM_API ARequestManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Request")
	float BlendTime = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Request")
	class URequestsData* RequestData = nullptr;

	UPROPERTY(EditAnywhere, Category = "References")
	ACameraActor* CameraActor;

	void PutRequest();
	bool TryPickUpRequest();
	void StartInteraction();
	void CancelInteraction();

	UFUNCTION(BlueprintCallable)
	void UpdateRequestType(RequestType p_type);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerDecision(ApproveType p_type);

	UFUNCTION(BlueprintCallable)
	void SignRequest();

	UFUNCTION(BlueprintCallable)
	bool VerifyRequest();
	
	UFUNCTION(BlueprintCallable)
	FRequest GenerateRequest();
	
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnInteractionStarted InteractionStarted;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnInteractionFinished InteractionFinished;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnRequestGenerated RequestGenerated;

private:
	virtual void BeginPlay() override;
	
	FString GenerateBirth();
	bool DrawIsAcceptable();
	FHandwrittenLetter GenerateLetter();
	FReport GenerateReport();
	ApproveType GenerateApproveType();
	

	void IsBlendingSetFalse();
	void IsInteractingSetFalse();

private:
	FRequest* m_PlayerRequest = nullptr;
	FRequest* m_CurrentRequest = nullptr;
	
	APlayerCharacter* m_PlayerCharacter = nullptr;
};
