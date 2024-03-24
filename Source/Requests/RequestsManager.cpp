// Damian Gorenski copyrights 2024

#include "RequestsManager.h"

void ARequestManager::BeginPlay()
{
	GenerateRequest();
}

#pragma region === Interaction Logic ====

void ARequestManager::StartInteraction()
{
	if (bIsInteracting)
	{
		return;
	}
	
	if (!CameraActor)
	{
		return;
	}

	RequestGenerated.Broadcast(*m_CurrentRequest);

	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	controller->SetViewTargetWithBlend(CameraActor, BlendTime);
	controller->bShowMouseCursor = true;
	controller->bEnableClickEvents = true;
	controller->bEnableMouseOverEvents = true;
	InteractionStarted.Broadcast();
	
	FTimerHandle Handle;
	bIsDuringBlend = true;
	bIsInteracting = true;
	GetWorldTimerManager().SetTimer(Handle, this, &ARequestManager::IsBlendingSetFalse, BlendTime, false);
}

void ARequestManager::CancelInteraction()
{
	if (!bIsInteracting)
	{
		return;
	}

	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	controller->bShowMouseCursor = false;
	controller->bEnableClickEvents = false;
	controller->bEnableMouseOverEvents = false;
	controller->SetViewTargetWithBlend(GetWorld()->GetFirstPlayerController()->GetPawn(),
																   BlendTime, VTBlend_Cubic);

	FTimerHandle InteractingHandle;
	FTimerHandle BlendingHandle;
	
	bIsDuringBlend = true;
	GetWorldTimerManager().SetTimer(InteractingHandle, this, &ARequestManager::IsInteractingSetFalse, BlendTime, false);
	GetWorldTimerManager().SetTimer(BlendingHandle, this, &ARequestManager::IsBlendingSetFalse, BlendTime, false);
	InteractionFinished.Broadcast();
}

void ARequestManager::IsBlendingSetFalse()
{
	bIsDuringBlend = false;
}

void ARequestManager::IsInteractingSetFalse()
{
	bIsInteracting = false;
}
#pragma endregion

#pragma region === Generate ===

FRequest* ARequestManager::GenerateRequest()
{	
	int randomNameNumber = FMath::RandRange(0, RequestData->Names.Num() - 1);
	FString randomName = RequestData->Names[randomNameNumber];

	int randomSurnameNumber = FMath::RandRange(0, RequestData->Surnames.Num() - 1);
	FString randomSurname = RequestData->Surnames[randomSurnameNumber];
	
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

FString ARequestManager::GenerateBirth()
{
	const int BirthDay = FMath::RandRange(1, 28);
	const int BirthMonth = FMath::RandRange(1, 12);
	const int BirthYear = FMath::RandRange(1902, 1925);

	FString birthDate = FString::FromInt(BirthMonth) + "." + FString::FromInt(BirthDay) + "." +
		FString::FromInt(BirthYear);

	return birthDate;
}

const FHandwrittenLetter& ARequestManager::GenerateLetter(bool p_good)
{
	if (p_good)
	{
		int Numbers = RequestData->GoodLetters.Num();
		int Value = FMath::RandRange(0, Numbers - 1);

		return RequestData->GoodLetters[Value];
	}

	// TODO unaccetable letters
	int Numbers = RequestData->GoodLetters.Num();
	int Value = FMath::RandRange(0, Numbers - 1);

	return RequestData->GoodLetters[Value];
}

ApproveType ARequestManager::GenerateApproveType()
{
	int Possibilites = StaticEnum<ApproveType>()->GetMaxEnumValue();
	int value = FMath::RandRange(0, Possibilites );

	return static_cast<ApproveType>(value);
}

#pragma endregion


