#pragma once

#include "FReport.h"
#include "RequestsData.h"
#include "FDescriptionData.h"
#include "FRequest.generated.h"

USTRUCT(BlueprintType)
struct FRequest
{
	GENERATED_BODY()

	FRequest() = default;
	FRequest(FString name, FString surname, FString birth, ApproveType approveType, FHandwrittenLetter letter,
	         FReport report);

#pragma region === Strings ===

	UPROPERTY(BlueprintReadOnly)
	FString RequesterName = "";

	UPROPERTY(BlueprintReadOnly)
	FString RequesterSurname = "";

	UPROPERTY(BlueprintReadOnly)
	FString RequesterDateOfBirth = "";

	UPROPERTY(BlueprintReadOnly)
	FString DateOfArrest = "";
	
#pragma endregion 
	
	UPROPERTY(BlueprintReadOnly)
	FHandwrittenLetter Letter;

	UPROPERTY(BlueprintReadOnly)
	FDescriptionData DescriptionData;

	// NYCID New york city identification
	UPROPERTY(BlueprintReadOnly)
	int32 Nysid = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 TopCharge = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 ArrestID = 0;

	UPROPERTY(BlueprintReadOnly)
	ApproveType Type = ApproveType::NONE;

	UPROPERTY(BlueprintReadOnly)
	FReport ReportData;

	bool bIsSigned = false;
};
