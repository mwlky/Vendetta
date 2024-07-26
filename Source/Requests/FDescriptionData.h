#pragma once

#include "FDescriptionData.generated.h"

USTRUCT(BlueprintType)
struct FDescriptionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Race = "White";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Sex = "Male";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SkinTone = "Light";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString HairType = "Short";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString HairColor = "Black";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString EyeColor = "Blue";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Height = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Weight = 0;
};
