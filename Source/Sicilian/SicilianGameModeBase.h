// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RequestManager.h"
#include "GameFramework/GameModeBase.h"
#include "Requests/RequestsData.h"
#include "SicilianGameModeBase.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStarted);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFinished);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestGenerated, FRequest, Request);

UCLASS()
class SICILIAN_API ASicilianGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartInteraction(ACameraActor* camera);
	void CancelInteraction();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Request")
	float BlendTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Request")
	bool bIsDuringBlend = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Request")
	bool bIsInteracting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Request")
	class URequestsData* RequestData = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnInteractionStarted InteractionStarted;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnInteractionFinished InteractionFinished;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnRequestGenerated RequestGenerated;

private:
	virtual void BeginPlay() override;
	void IsBlendingSetFalse();
	void IsInteractingSetFalse();

	RequestManager* m_RequestManager = nullptr;
};
