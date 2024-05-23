// Damian Gorenski copyrights 2024

#include "HudManager.h"

#include "Blueprint/UserWidget.h"

void AHudManager::BeginPlay()
{
	m_DotInteractableWidget = Cast<UDotWidget>(CreateWidget<UUserWidget>(GetWorld(), DotInteractableWidgetClass));
	m_DotInteractableWidget->AddToViewport();
	m_DotInteractableWidget->SetVisibility(ESlateVisibility::Hidden);

	m_DotWidget = Cast<UDotWidget>(CreateWidget<UUserWidget>(GetWorld(), DotWidgetClass));
	m_DotWidget->AddToViewport();

	ShowBasicDot(true);
}

#pragma region === Dot Logic ===

void AHudManager::HideAllDots()
{
	if (bIsNormalDot)
		m_DotWidget->SetVisibility(ESlateVisibility::Hidden);
	else
		m_DotInteractableWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AHudManager::ShowBasicDot(bool HidePrevious)
{
	if (m_DotWidget == nullptr)
		return;

	if (bIsNormalDot)
		return;

	if (!bIsNormalDot && HidePrevious)
	{
		m_DotInteractableWidget->OutAnimation();
		m_DotInteractableWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	bIsNormalDot = true;

	m_DotWidget->SetVisibility(ESlateVisibility::Visible);
	m_DotWidget->PlayAnimation();
}

void AHudManager::ShowInteractableDot(bool HidePrevious)
{
	if (m_DotInteractableWidget == nullptr)
		return;

	if (!bIsNormalDot)
		return;

	if (bIsNormalDot && HidePrevious)
	{
		m_DotWidget->OutAnimation();
		m_DotWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	bIsNormalDot = false;
	
	m_DotInteractableWidget->SetVisibility(ESlateVisibility::Visible);
	m_DotInteractableWidget->PlayAnimation();
}
#pragma endregion
