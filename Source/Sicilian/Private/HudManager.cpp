// Damian Gorenski copyrights 2024


#include "HudManager.h"
#include "Blueprint/UserWidget.h"


void AHudManager::ShowDot()
{
	if (m_DotWidget)
		m_DotWidget->AddToViewport();
}

void AHudManager::HideDots()
{
	if (m_DotWidget)
		m_DotWidget->RemoveFromParent();
}

void AHudManager::BeginPlay()
{
	m_DotWidget = CreateWidget<UUserWidget>(GetWorld(), DotWidgetClass);
	m_DotWidget->AddToViewport();
}
