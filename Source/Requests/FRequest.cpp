#include "FRequest.h"

FRequest::FRequest(FString name, FString surname, FString birth, ApproveType approveType, FHandwrittenLetter letter)
{
	Letter = letter;
	Type = approveType;
	
	RequesterName = name;
	RequesterSurname = surname;

	RequesterDateOfBirth = birth; 
}
