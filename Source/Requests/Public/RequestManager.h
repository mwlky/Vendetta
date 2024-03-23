// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Requests/RequestsData.h"
#include "Requests/FRequest.h"

class REQUESTSYSTEM_API RequestManager
{
public:
	RequestManager(URequestsData* RequestsData);
	~RequestManager();

	void StartInteraction();
	FRequest* GenerateRequest();

private:
	FString GenerateBirth();
	const FHandwrittenLetter& GenerateLetter(bool p_isAcceptable);
	ApproveType GenerateApproveType();

private:
	FRequest* m_CurrentRequest = nullptr;
	URequestsData* m_RequestData = nullptr;
};
