// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Blueprint/UserWidget.h"

#include "HudManager.generated.h"

UCLASS()
class SICILIAN_API AHudManager : public AHUD
{
	GENERATED_BODY()

public:
	void ShowDot();
	void HideDots();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> DotWidgetClass = nullptr;
	
private:
	virtual void BeginPlay() override;

	UUserWidget* m_DotWidget = nullptr;
};
