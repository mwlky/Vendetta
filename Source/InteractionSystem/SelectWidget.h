// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class INTERACTIONSYSTEM_API USelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void InjectAnimation(UWidgetAnimation* Animation);

	void ReverseAnimation();
	void PlayAnimation(UTexture2D* TextureToShow);
	
private:

	UPROPERTY(EditAnywhere)
	float m_PlaybackSpeed = 1.5f;

	UPROPERTY(meta = (BindWidget))
	UImage* Icon = nullptr;
	
	UWidgetAnimation* m_Animation = nullptr;

	bool m_IsPlayed = false;
};
