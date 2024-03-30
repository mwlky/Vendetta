﻿#include "FRequest.h"

FRequest::FRequest(FString name, FString surname, FString birth, ApproveType approveType, FHandwrittenLetter letter,
                   FReport report)
{
	Letter = letter;
	Type = approveType;

	RequesterName = name;
	RequesterSurname = surname;

	RequesterDateOfBirth = birth;

	ReportData = report;
}
