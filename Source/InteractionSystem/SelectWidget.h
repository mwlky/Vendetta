// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectWidget.generated.h"

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

	void PlayAnimation();
	void ReverseAnimation();
	
private:

	UPROPERTY(EditAnywhere)
	float m_PlaybackSpeed = 1.5f;
	
	UWidgetAnimation* m_Animation = nullptr;

	bool m_IsPlayed = false;
};
