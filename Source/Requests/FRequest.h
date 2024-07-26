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
	FRequest(FString name, FString surname, FString birth, ApproveType approveType, const FHandwrittenLetter& letter,
	         const FReport& report, const FDescriptionData& DescriptionData);

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
	FString Nysid;

	UPROPERTY(BlueprintReadOnly)
	FString TopCharge;

	UPROPERTY(BlueprintReadOnly)
	FString ArrestID;

	UPROPERTY(BlueprintReadOnly)
	FString CrimeDate = "";

	UPROPERTY(BlueprintReadOnly)
	int CrimeAge = 0;
 	
	UPROPERTY(BlueprintReadOnly)
	ApproveType Type = ApproveType::NONE;

	UPROPERTY(BlueprintReadOnly)
	FReport ReportData;

	bool bIsSigned = false;
};
