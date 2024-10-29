// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OEBGameInstance.generated.h"


class USessionTracker;

UCLASS()
class OEB_API UOEBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UOEBGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION()
	void LoadConfigFromBackend(FString ConfigID, bool bRefreshInstances);

	UPROPERTY(Transient)
	USessionTracker* SessionTracker;
};



