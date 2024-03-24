// Damian Gorenski copyrights 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RequestWidget.generated.h"

class ARequestManager;
/**
 * 
 */
UCLASS()
class REQUESTSYSTEM_API URequestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ref")
	ARequestManager* RequestManager;
	
};
