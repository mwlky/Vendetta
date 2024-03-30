// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RequestsData.generated.h"

UENUM()
enum class ApproveType : uint8
{
	Approved = 0,
	Denied   = 1,
};

UENUM()
enum class RequestType : uint8
{
	Vacation       = 0,
	TimeOffWithPay = 1,
	SickTime       = 2,
	MilitaryLeave  = 3,
	PersonalDay    = 4,
	BereavementDay = 5
};

USTRUCT(BlueprintType)
struct FHandwrittenLetter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FString LetterText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	RequestType RequestType;
};

UCLASS()
class REQUESTSYSTEM_API URequestsData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Names;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Surnames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	TArray<FHandwrittenLetter> GoodLetters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	TArray<FHandwrittenLetter> UnacceptableLetters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	TArray<FString> GoodReports;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	TArray<FString> Signs;
};
