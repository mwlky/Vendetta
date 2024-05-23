// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DotWidget.generated.h"

/**
 * 
 */
UCLASS()
class SICILIAN_API UDotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void OutAnimation();
	void PlayAnimation();
	
private:
	UFUNCTION(BlueprintCallable)
	void InjectAnimation(UWidgetAnimation* Animation);

	UWidgetAnimation* m_Animation = nullptr;
};
