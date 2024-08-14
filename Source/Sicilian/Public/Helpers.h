// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Helpers.generated.h"

/**
 * 
 */
UCLASS()
class SICILIAN_API UHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Ui")
	static TArray<FString> ConvertTextToString(const FString& string);
};
