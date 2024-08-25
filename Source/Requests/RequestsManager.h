// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Requests/FRequest.h"
#include "Camera/CameraActor.h"
#include "Requests/RequestsData.h"
#include "Kismet/GameplayStatics.h"
#include "Sicilian/PlayerCharacter.h"
#include "RequestsManager.generated.h"

class AARequestHolder;
class ASicillianPlayerController;
class AHudManager;

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStarted);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFinished);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestPickedUp);

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
	void StartInteraction();
	void CancelInteraction();
	
	bool TryPickUpRequest();
	bool IsRequestSigned() const;

	UFUNCTION(BlueprintCallable)
	void UpdateRequestType(RequestType p_type);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerDecision(ApproveType p_type);

	UFUNCTION(BlueprintCallable)
	bool TrySignRequest();

	UFUNCTION(BlueprintCallable)
	bool VerifyRequest();

	UFUNCTION(BlueprintPure, Category = "Request")
	FRequest GetCurrentRequest() const { return *m_CurrentRequest; }
	
	UFUNCTION(BlueprintCallable)
	FRequest GenerateRequest();
	
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnInteractionStarted InteractionStarted;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnInteractionFinished InteractionFinished;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnRequestGenerated RequestGenerated;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnRequestPickedUp RequestPickedUp;
	
private:
	virtual void BeginPlay() override;
	
	bool DrawIsAcceptable();
	void DrawRequestHolder();
	void IsBlendingSetFalse();
	void IsInteractingSetFalse();
	
	ApproveType GenerateApproveType();
	
	FReport GenerateReport();
	FString GenerateBirth();
	FHandwrittenLetter GenerateLetter();
	FDescriptionData GenerateDescription();

private:
	UPROPERTY(EditAnywhere, Category = "References")
	TArray<AARequestHolder*> m_Holders;
	
	UPROPERTY(BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true"))
	bool bIsLetterOpened = false;
	
	FRequest* m_PlayerRequest = nullptr;
	FRequest* m_CurrentRequest = nullptr;
	
	AHudManager* m_HudManager = nullptr;
	APlayerCharacter* m_PlayerCharacter = nullptr;
	ASicillianPlayerController* m_PlayerController = nullptr;
};
