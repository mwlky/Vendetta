// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RequestsData.generated.h"

UENUM(BlueprintType)
enum class EApproveType : uint8
{
	None     = 0,
	Approved = 1,
	Denied   = 2,
};

UENUM(BlueprintType)
enum class ERequestType : uint8
{
	None           = 0,
	Vacation       = 1,
	TimeOffWithPay = 2,
	SickTime       = 3,
	MilitaryLeave  = 4,
	PersonalDay    = 5,
	BereavementDay = 6
};

USTRUCT(BlueprintType)
struct FHandwrittenLetter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FString LetterText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERequestType RequestType = ERequestType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAcceptable = false;
};

UCLASS()
class REQUESTSYSTEM_API URequestsData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int ChanceForUnacceptableLetter;
	
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
	TArray<FString> BadReports;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	TArray<FString> Signs;
};
