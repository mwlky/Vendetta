// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RequestWidget.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInjected);

class UTextBlock;
class ARequestManager;

UCLASS()
class REQUESTSYSTEM_API URequestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInject();

	UFUNCTION(BlueprintCallable)
	void AdjustFontSize(UTextBlock* textBlock, FText text);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ref")
	ARequestManager* RequestManager = nullptr;

protected:
	virtual void NativeConstruct() override;
};
