#include "FRequest.h"

FRequest::FRequest(FString name, FString surname, FString birth, ApproveType approveType, const FHandwrittenLetter& letter,
                   const FReport& report, const FDescriptionData& DescriptionData)
{
	Letter = letter;
	Type = approveType;
	ReportData = report;
	RequesterName = name;
	RequesterSurname = surname;
	RequesterDateOfBirth = birth;
	this->DescriptionData = DescriptionData;

	int32 IdNumber = FMath::RandRange(5719,89123);
	Nysid = FString::FromInt(IdNumber) + "#";

	int32 ChargeNumber = FMath::RandRange(45123, 98431);
	TopCharge = FString::FromInt(ChargeNumber) + "#";

	int32 ArrestId = FMath::RandRange(2345, 89123);
	ArrestID = FString::FromInt(ArrestId) + "#";

	int32 RandomTopCharge = FMath::RandRange(2345, 89123);
	TopCharge = FString::FromInt(RandomTopCharge) + "#";

	int32 YearOfBirth = FCString::Atoi(*birth.RightChop(birth.Len() - 4));
	uint32 YearOfCrime = FMath::RandRange(YearOfBirth + 15, 1950);
	CrimeAge = YearOfCrime - YearOfBirth;

	uint32 CrimeDay = FMath::RandRange(1, 25);
	uint32 CrimeMonth = FMath::RandRange(1, 12);
	CrimeDate = FString::FromInt(CrimeMonth) + "." + FString::FromInt(CrimeDay) + "." + FString::FromInt(YearOfCrime);
}
