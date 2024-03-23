#pragma once
#include "RequestsData.h"
#include "FRequest.generated.h"

USTRUCT(BlueprintType)
struct FRequest
{
	GENERATED_BODY()

	FRequest() = default;
	FRequest(FString name, FString surname, FString birth, ApproveType approveType, FHandwrittenLetter letter);

public:
	UPROPERTY(BlueprintReadOnly)
	FString RequesterName;

	UPROPERTY(BlueprintReadOnly)
	FString RequesterSurname;

	UPROPERTY(BlueprintReadOnly)
	FString RequesterDateOfBirth;

	UPROPERTY(BlueprintReadOnly)
	FHandwrittenLetter Letter;

	UPROPERTY(BlueprintReadOnly)
	ApproveType Type;
};
