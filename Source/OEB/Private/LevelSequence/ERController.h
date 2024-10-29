// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ERController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AERController : public AInfo
{
	GENERATED_BODY()
public:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ConnectActorToER(class UERActorComponent* ERActorComponent, bool bShowERWidget = true);
};
