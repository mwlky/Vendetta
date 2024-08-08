// Damian Gorenski copyrights 2024


#include "RequestWidget.h"

#include "Components/TextBlock.h"

void URequestWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URequestWidget::AdjustFontSize(UTextBlock* textBlock, FText text)
{
	if(!textBlock)
		return;
	
	int32 TextLength = text.ToString().Len();
	int32 NewFontSize = 0;

	if (TextLength <= 500)
		NewFontSize = 20;
	
	else if (TextLength <= 1000)
		NewFontSize = 18;
	
	else
		NewFontSize = 10;
	
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Blue, FString::FromInt(NewFontSize));

	FSlateFontInfo FontInfo = textBlock->GetFont();
	FontInfo.Size = NewFontSize;
	textBlock->SetFont(FontInfo);
}
