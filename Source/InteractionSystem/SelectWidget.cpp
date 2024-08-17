// Damian Gorenski copyrights 2024


#include "SelectWidget.h"

void USelectWidget::InjectAnimation(UWidgetAnimation* Animation)
{
	m_Animation = Animation;
}

void USelectWidget::PlayAnimation()
{
	if(!m_Animation)
		return;

	if(m_IsPlayed)
		return;

	m_IsPlayed = true;
	
	UUserWidget::PlayAnimation(m_Animation, 0, 1.f, EUMGSequencePlayMode::Forward, m_PlaybackSpeed);
}

void USelectWidget::ReverseAnimation()
{
	if(!m_IsPlayed)
		return;

	m_IsPlayed = false;
	
	UUserWidget::PlayAnimation(m_Animation, 0, 1.f, EUMGSequencePlayMode::Reverse, m_PlaybackSpeed);
}
