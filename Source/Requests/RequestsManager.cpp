// Damian Gorenski copyrights 2024

#include "RequestsManager.h"

#include "SicilianPlayerController.h"
#include "Camera/CameraActor.h"

void ARequestManager::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	m_PlayerCharacter = Cast<APlayerCharacter>(Character);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	m_PlayerController = Cast<ASicilianPlayerController>(PlayerController);

	m_PlayerRequest = new FRequest;
	m_PlayerRequest->Letter = FHandwrittenLetter();
}

#pragma region === Interaction Logic ====

void ARequestManager::StartInteraction()
{
	if (m_PlayerCharacter->bIsInteracting || m_CurrentRequest->bIsSigned)
		return;

	if (!CameraActor)
		return;

	if (!m_PlayerController)
		return;

	m_PlayerController->SwitchCameraView(CameraActor, true);

	InteractionStarted.Broadcast();
}

void ARequestManager::CancelInteraction()
{
	if (!m_PlayerCharacter->bIsInteracting)
		return;

	if (!m_PlayerController)
		return;

	m_PlayerController->SwitchCameraToPlayerDefault();

	InteractionFinished.Broadcast();
}

void ARequestManager::UpdateRequestType(ERequestType p_type)
{
	m_PlayerRequest->Letter.RequestType = p_type;
}

void ARequestManager::UpdatePlayerDecision(EApproveType p_type)
{
	m_PlayerRequest->Type = p_type;
}

bool ARequestManager::VerifyRequest()
{
	if (m_CurrentRequest->Letter.RequestType != m_PlayerRequest->Letter.RequestType)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong request type!"))
		return false;
	}

	if (m_CurrentRequest->Type != m_PlayerRequest->Type)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong decision!"))
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Good!"))
	return true;
}

bool ARequestManager::TrySign()
{
	if (m_PlayerRequest->Type == EApproveType::None)
	{
		return false;
	}

	if (m_PlayerRequest->Letter.RequestType == ERequestType::None)
	{
		return false;
	}

	CancelInteraction();
	m_CurrentRequest->bIsSigned = true;

	return true;
}
#pragma endregion

#pragma region === Generate ===

FRequest ARequestManager::GenerateRequest()
{
	int randomNameNumber = FMath::RandRange(0, RequestData->Names.Num() - 1);
	FString randomName = RequestData->Names[randomNameNumber];

	int randomSurnameNumber = FMath::RandRange(0, RequestData->Surnames.Num() - 1);
	FString randomSurname = RequestData->Surnames[randomSurnameNumber];

	FString BirthDate = GenerateBirth();

	FHandwrittenLetter Letter = GenerateLetter();

	FReport report = GenerateReport();

	if (m_CurrentRequest != nullptr)
	{
		delete m_CurrentRequest;
	}

	EApproveType Approve = EApproveType::Approved;
	if (!report.bIsAcceptable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unacceptable cause of report!"));
		Approve = EApproveType::Denied;
	}

	else if (!Letter.bIsAcceptable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unacceptable cause of letter!"));
		Approve = EApproveType::Denied;
	}

	m_CurrentRequest = new FRequest(randomName, randomSurname, BirthDate, Approve, Letter, report);
	RequestGenerated.Broadcast(*m_CurrentRequest);

	return *m_CurrentRequest;
}

FString ARequestManager::GenerateBirth()
{
	const int BirthDay = FMath::RandRange(1, 28);
	const int BirthMonth = FMath::RandRange(1, 12);
	const int BirthYear = FMath::RandRange(1902, 1925);

	FString birthDate = FString::FromInt(BirthMonth) + "." + FString::FromInt(BirthDay) + "." +
		FString::FromInt(BirthYear);

	return birthDate;
}

bool ARequestManager::DrawIsAcceptable()
{
	int Draw = FMath::RandRange(0, 100);
	return Draw > RequestData->ChanceForUnacceptableLetter;
}

FHandwrittenLetter ARequestManager::GenerateLetter()
{
	bool bIsAcceptable = DrawIsAcceptable();

	if (bIsAcceptable)
	{
		int Numbers = RequestData->GoodLetters.Num();
		int Value = FMath::RandRange(0, Numbers - 1);

		return RequestData->GoodLetters[Value];
	}

	int Numbers = RequestData->UnacceptableLetters.Num();
	int Value = FMath::RandRange(0, Numbers - 1);

	return RequestData->UnacceptableLetters[Value];
}

EApproveType ARequestManager::GenerateApproveType()
{
	int Possibilites = StaticEnum<EApproveType>()->GetMaxEnumValue();
	int value = FMath::RandRange(0, Possibilites);

	return static_cast<EApproveType>(value);
}

FReport ARequestManager::GenerateReport()
{
	// TODO Fake sings
	int PossibilitesForSign = RequestData->Signs.Num();
	int RandomSignValue = FMath::RandRange(0, PossibilitesForSign - 1);

	FString Sign = RequestData->Signs[RandomSignValue];
	FString Text;

	bool bAcceptable = DrawIsAcceptable();

	if (bAcceptable)
	{
		int PossibilitiesReport = RequestData->GoodReports.Num();
		int RandomReport = FMath::RandRange(0, PossibilitiesReport - 1);
		Text = RequestData->GoodReports[RandomReport];
	}

	else
	{
		int PossibilitiesReport = RequestData->BadReports.Num();
		int RandomReport = FMath::RandRange(0, PossibilitiesReport - 1);
		Text = RequestData->BadReports[RandomReport];
	}

	return FReport(Sign, bAcceptable, Text);
}


#pragma endregion
