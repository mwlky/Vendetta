// Damian Gorenski copyrights 2024

#include "DotWidget.h"

void UDotWidget::OutAnimation()
{
	if(!m_Animation)
		return;

	UUserWidget::PlayAnimation(m_Animation, 0.f, 1, EUMGSequencePlayMode::Reverse, 1);
}

void UDotWidget::PlayAnimation()
{
	if(!m_Animation)
		return;

	UUserWidget::PlayAnimation(m_Animation, 0.f, 1, EUMGSequencePlayMode::Forward, 1);
}

void UDotWidget::InjectAnimation(UWidgetAnimation* Animation)
{
	m_Animation = Animation;
}
