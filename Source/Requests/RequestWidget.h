// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RequestWidget.generated.h"

class UTextBlock;
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInjected);

class ARequestManager;

UCLASS()
class REQUESTSYSTEM_API URequestWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ref")
	ARequestManager* RequestManager;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInject();

	UFUNCTION(BlueprintCallable)
	void AdjustFontSize(UTextBlock* textBlock, FText text);
};
