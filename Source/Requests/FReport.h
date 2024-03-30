#pragma once

#include "FReport.generated.h"

USTRUCT(BlueprintType)
struct FReport
{
	GENERATED_BODY()
	
	FReport() = default;
	FReport(FString sign, bool isFake, FString text);

	UPROPERTY(BlueprintReadOnly)
	FString Text;
	
	UPROPERTY(BlueprintReadOnly)
	FString Sign;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFake;
};
