#pragma once

#include "FDescriptionData.generated.h"

UENUM(BlueprintType)
enum class ESex : uint8
{
	NONE  = 0,
	Man   = 1,
	Woman = 2
};

UENUM(BlueprintType)
enum class ERace : uint8
{
	NONE   = 0,
	White  = 1,
	Black  = 2
};

UENUM(BlueprintType)
enum class EColors : uint8 
{
	NONE   = 0,
	Black  = 1,
	Blond  = 2,
	Blue   = 3,
	Brown  = 4,
	Red    = 5
};

UENUM(BlueprintType)
enum class EHairType : uint8
{
	NONE   = 0,
	Short  = 1,
	Medium = 2,
	Long   = 3
};

UENUM(BlueprintType)
enum class ESkinTone : uint8
{
	NONE   = 0,
	Light  = 1,
	Dark   = 2
};

USTRUCT(BlueprintType)
struct FDescriptionData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FString Race = "White";
	
	UPROPERTY(BlueprintReadWrite)
	FString Sex = "Male";
	
	UPROPERTY(BlueprintReadWrite)
	FString SkinTone = "Light";
	
	UPROPERTY(BlueprintReadWrite)
	FString HairType = "Short";
	
	UPROPERTY(BlueprintReadWrite)
	FString HairColor = "Black";
	
	UPROPERTY(BlueprintReadWrite)
	FString EyeColor = "Blue";
	
	UPROPERTY(BlueprintReadWrite)
	int32 Height = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 Weight = 0;
};
