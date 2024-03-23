// Damian Gorenski copyrights 2024


#include "RequestManager.h"


RequestManager::RequestManager(URequestsData* RequestsData)
{
	m_RequestData = RequestsData;
}

RequestManager::~RequestManager()
{
}

void RequestManager::StartInteraction()
{
	GenerateRequest();
}

#pragma region === Generate ===

FRequest* RequestManager::GenerateRequest()
{
	int randomNameNumber = FMath::RandRange(0, m_RequestData->Names.Num() - 1);
	FString randomName = m_RequestData->Names[randomNameNumber];

	int randomSurnameNumber = FMath::RandRange(0, m_RequestData->Surnames.Num() - 1);
	FString randomSurname = m_RequestData->Surnames[randomSurnameNumber];
	
	FString BirthDate = GenerateBirth();
	
	ApproveType approveType = GenerateApproveType();
	FHandwrittenLetter Letter = GenerateLetter(approveType == ApproveType::Approved);

	if (m_CurrentRequest != nullptr)
	{
		delete m_CurrentRequest;
	}

	m_CurrentRequest = new FRequest(randomName, randomSurname, BirthDate, approveType, Letter);

	return m_CurrentRequest;
}

FString RequestManager::GenerateBirth()
{
	const int BirthDay = FMath::RandRange(1, 28);
	const int BirthMonth = FMath::RandRange(1, 12);
	const int BirthYear = FMath::RandRange(1902, 1925);

	FString birthDate = FString::FromInt(BirthMonth) + "." + FString::FromInt(BirthDay) + "." +
		FString::FromInt(BirthYear);

	return birthDate;
}

const FHandwrittenLetter& RequestManager::GenerateLetter(bool p_good)
{
	if (p_good)
	{
		int Numbers = m_RequestData->GoodLetters.Num();
		int Value = FMath::RandRange(0, Numbers - 1);

		return m_RequestData->GoodLetters[Value];
	}

	// TODO unaccetable letters
	int Numbers = m_RequestData->GoodLetters.Num();
	int Value = FMath::RandRange(0, Numbers - 1);

	return m_RequestData->GoodLetters[Value];
}

ApproveType RequestManager::GenerateApproveType()
{
	int Possibilites = StaticEnum<ApproveType>()->GetMaxEnumValue();
	int value = FMath::RandRange(0, Possibilites );

	return static_cast<ApproveType>(value);
}

#pragma endregion


