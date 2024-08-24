// Damian Gorenski copyrights 2024

#include "RequestsManager.h"

#include "ARequestHolder.h"
#include "HudManager.h"
#include "SicillianPlayerController.h"

#define DEBUG(x) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, x);

void ARequestManager::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	m_PlayerCharacter = Cast<APlayerCharacter>(Character);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	m_PlayerController = Cast<ASicillianPlayerController>(Controller);

	m_HudManager = Cast<AHudManager>(Controller->GetHUD());

	m_PlayerRequest = new FRequest;
	m_PlayerRequest->Letter = FHandwrittenLetter();
}

#pragma region === Interaction Logic ====

void ARequestManager::PutRequest()
{
	if (!m_PlayerCharacter->bPickedUpRequest)
		return;

	m_PlayerCharacter->bPickedUpRequest = false;
	GenerateRequest();
}

bool ARequestManager::TryPickUpRequest()
{
	if (!m_PlayerRequest->bIsSigned)
		return false;

	m_PlayerCharacter->bPickedUpRequest = true;
	RequestPickedUp.Broadcast();
	DrawRequestHolder();

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

	if (!m_PlayerController)
		return;

	m_HudManager->HideAllDots();
	m_PlayerController->bShowMouseCursor = true;
	m_PlayerController->SetInputMode(FInputModeGameAndUI());
	m_PlayerController->SetViewTargetWithBlend(CameraActor, BlendTime, VTBlend_Cubic);

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

	if (!m_PlayerController)
		return;

	if (m_HudManager)
		m_HudManager->ShowBasicDot(true);

	m_PlayerController->bShowMouseCursor = false;
	m_PlayerController->SetInputMode(FInputModeGameOnly());
	m_PlayerController->SetViewTargetWithBlend(m_PlayerCharacter, BlendTime, VTBlend_Cubic);

	m_PlayerCharacter->bIsBlending = true;

	FTimerHandle InteractingHandle;
	FTimerHandle BlendingHandle;

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
	FDescriptionData DescriptionData = GenerateDescription();

	if (m_CurrentRequest != nullptr)
		delete m_CurrentRequest;

	ApproveType Approve = ApproveType::Approved;

	m_PlayerRequest->bIsSigned = false;
	m_PlayerCharacter->bPickedUpRequest = false;

	m_CurrentRequest = new FRequest(randomName, randomSurname, BirthDate, Approve, Letter, report, DescriptionData);
	RequestGenerated.Broadcast(*m_CurrentRequest);

	return *m_CurrentRequest;
}

FString ARequestManager::GenerateBirth()
{
	int BirthDay = FMath::RandRange(1, 28);
	int BirthMonth = FMath::RandRange(1, 12);
	int BirthYear = FMath::RandRange(1902, 1925);

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

FDescriptionData ARequestManager::GenerateDescription()
{
	TArray<FDescriptionData> Possibilities = RequestData->Descriptions;
	int32 Amount = Possibilities.Num();
	int32 Drawn = FMath::RandRange(0, Amount - 1);

	return Possibilities[Drawn];
}

void ARequestManager::DrawRequestHolder()
{
	int Random = FMath::RandRange(0, m_Holders.Num() - 1);

	AARequestHolder* DrawnRequestHolder = m_Holders[Random];
	DrawnRequestHolder->Activate();
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
