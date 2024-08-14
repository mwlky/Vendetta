// Damian Gorenski copyrights 2024


#include "Helpers.h"

TArray<FString> UHelpers::ConvertTextToString(const FString& string)
{
	TArray<FString> CharacterArray;

	for (int i = 0; i < string.Len(); ++i)
	{
		FString Character = string.Mid(i, 1);
		CharacterArray.Add(Character);
	}

	return CharacterArray;
}
