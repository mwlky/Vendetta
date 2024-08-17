// Damian Gorenski copyrights 2024

#include "HudManager.h"

#include "Blueprint/UserWidget.h"
#include "InteractionSystem/SelectWidget.h"

void AHudManager::BeginPlay()
{
	Super::BeginPlay();

	m_DotInteractableWidget = CreateWidget<UDotWidget>(GetWorld(), DotInteractableWidgetClass);
	m_DotInteractableWidget->AddToViewport();
	m_DotInteractableWidget->SetVisibility(ESlateVisibility::Hidden);

	m_DotWidget = CreateWidget<UDotWidget>(GetWorld(), DotWidgetClass);
	m_DotWidget->AddToViewport();

	m_SelectWidget = CreateWidget<USelectWidget>(GetWorld(), SelectWidget);
	m_SelectWidget->AddToViewport();

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

void AHudManager::SetSelectPanelActivity(bool Activity)
{
	if (!m_SelectWidget)
		return;

	if (Activity)
		m_SelectWidget->PlayAnimation();

	else
		m_SelectWidget->ReverseAnimation();
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
