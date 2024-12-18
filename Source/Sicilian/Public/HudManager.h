// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "DotWidget.h"
#include "GameFramework/HUD.h"

#include "Blueprint/UserWidget.h"

#include "HudManager.generated.h"

UCLASS()
class SICILIAN_API AHudManager : public AHUD
{
	GENERATED_BODY()

public:
	void HideAllDots();
	void ShowBasicDot(bool HidePrevious);
	void SetSelectPanelActivity(bool Activity, UTexture2D* TextureToShow);
	void ShowInteractableDot(bool HidePrevious);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> DotWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> DotInteractableWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class USelectWidget> SelectWidget = nullptr;
	
private:
	virtual void BeginPlay() override;

	UDotWidget* m_DotWidget = nullptr;
	USelectWidget* m_SelectWidget = nullptr;
	UDotWidget* m_DotInteractableWidget = nullptr;
	
	bool bIsNormalDot = false;
};
