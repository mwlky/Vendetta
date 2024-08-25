// Damian Gorenski copyrights 2024


#include "SelectWidget.h"

#include "Components/Image.h"

void USelectWidget::InjectAnimation(UWidgetAnimation* Animation)
{
	m_Animation = Animation;
}

void USelectWidget::PlayAnimation(UTexture2D* TextureToShow)
{
	if(!m_Animation)
		return;

	if(m_IsPlayed)
		return;

	m_IsPlayed = true;
	if(Icon)
		Icon->SetBrushFromTexture(TextureToShow, true);
	
	UUserWidget::PlayAnimation(m_Animation, 0, 1.f, EUMGSequencePlayMode::Forward, m_PlaybackSpeed);
}

void USelectWidget::ReverseAnimation()
{
	if(!m_IsPlayed)
		return;

	m_IsPlayed = false;
	
	UUserWidget::PlayAnimation(m_Animation, 0, 1.f, EUMGSequencePlayMode::Reverse, m_PlaybackSpeed);
}
