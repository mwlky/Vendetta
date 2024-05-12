// Damian Gorenski copyrights 2024

#include "RequestsManager.h"

#define DEBUG(x) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, x);

void ARequestManager::BeginPlay()
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	m_PlayerCharacter = Cast<APlayerCharacter>(Character);

	m_PlayerRequest = new FRequest;
	m_PlayerRequest->Letter = FHandwrittenLetter();

	GenerateRequest();
}

#pragma region === Interaction Logic ====

void ARequestManager::PutRequest()
{
	if (!m_PlayerCharacter->bPickedUpRequest)
	{
		return;
	}

	m_PlayerCharacter->bPickedUpRequest = false;
	GenerateRequest();
}

bool ARequestManager::TryPickUpRequest()	
{
	if (!m_PlayerRequest->bIsSigned)
		return false;

	m_PlayerCharacter->bPickedUpRequest = true;
	RequestPickedUp.Broadcast();
	return true;
}

void ARequestManager::StartInteraction()
{
	if (m_PlayerCharacter->bIsInteracting)
		return;

	if (m_PlayerRequest->bIsSigned)
		return;

	if (!CameraActor)
		return;

	APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);

	if (!controller)
		return;

	controller->bShowMouseCursor = true;
	controller->SetViewTargetWithBlend(CameraActor, BlendTime, VTBlend_Linear);

	controller->SetInputMode(FInputModeGameAndUI());
	
	InteractionStarted.Broadcast();

	FTimerHandle Handle;
	m_PlayerCharacter->bIsBlending = true;
	m_PlayerCharacter->bIsInteracting = true;
	GetWorldTimerManager().SetTimer(Handle, this, &ARequestManager::IsBlendingSetFalse, BlendTime, false);
}

void ARequestManager::CancelInteraction()
{
	if (!m_PlayerCharacter->bIsInteracting)
		return;

	APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);

	if (!controller)
		return;

	controller->bShowMouseCursor = false;
	controller->SetInputMode(FInputModeGameOnly());
	controller->SetViewTargetWithBlend(m_PlayerCharacter, BlendTime);

	FTimerHandle InteractingHandle;
	FTimerHandle BlendingHandle;

	m_PlayerCharacter->bIsBlending = true;

	GetWorldTimerManager().SetTimer(InteractingHandle, this, &ARequestManager::IsInteractingSetFalse, BlendTime, false);
	GetWorldTimerManager().SetTimer(BlendingHandle, this, &ARequestManager::IsBlendingSetFalse, BlendTime, false);

	InteractionFinished.Broadcast();
}

void ARequestManager::UpdateRequestType(RequestType p_type)
{
	m_PlayerRequest->Letter.RequestType = p_type;
}

void ARequestManager::UpdatePlayerDecision(ApproveType p_type)
{
	m_PlayerRequest->Type = p_type;
}

bool ARequestManager::TrySignRequest()
{
	if (m_PlayerRequest->Type == ApproveType::NONE)
	{
		DEBUG("No decision for approve!");
		return false;
	}

	if (m_PlayerRequest->Letter.RequestType == RequestType::NONE)
	{
		DEBUG("No decision for letter!");
		return false;
	}
	
	m_PlayerRequest->bIsSigned = true;
	CancelInteraction();
	return true;
}

bool ARequestManager::VerifyRequest()
{
	if (m_CurrentRequest->Letter.RequestType != m_PlayerRequest->Letter.RequestType)
		return false;

	if (m_CurrentRequest->Type != m_PlayerRequest->Type)
		return false;

	return true;
}

void ARequestManager::IsBlendingSetFalse()
{
	m_PlayerCharacter->bIsBlending = false;
}

void ARequestManager::IsInteractingSetFalse()
{
	m_PlayerCharacter->bIsInteracting = false;
}
#pragma endregion

#pragma region === Generate ===

FRequest ARequestManager::GenerateRequest()
{
	int randomNameNumber = FMath::RandRange(0, RequestData->Names.Num() - 1);
	FString randomName = RequestData->Names[randomNameNumber];

	int randomSurnameNumber = FMath::RandRange(0, RequestData->Surnames.Num() - 1);
	FString randomSurname = RequestData->Surnames[randomSurnameNumber];

	FReport report = GenerateReport();
	FString BirthDate = GenerateBirth();
	FHandwrittenLetter Letter = GenerateLetter();

	if (m_CurrentRequest != nullptr)
		delete m_CurrentRequest;

	ApproveType Approve = ApproveType::Approved;

	m_PlayerRequest->bIsSigned = false;
	m_PlayerCharacter->bPickedUpRequest = false;
	
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

ApproveType ARequestManager::GenerateApproveType()
{
	int Possibilites = StaticEnum<ApproveType>()->GetMaxEnumValue();
	int value = FMath::RandRange(0, Possibilites);

	return static_cast<ApproveType>(value);
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
