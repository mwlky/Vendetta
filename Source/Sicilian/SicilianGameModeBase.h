// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SicilianGameModeBase.generated.h"

UCLASS()
class SICILIAN_API ASicilianGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
};
