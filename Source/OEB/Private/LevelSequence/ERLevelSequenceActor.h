// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "ERLevelSequenceActor.generated.h"

/**
 * 
 */
UCLASS()
class AERLevelSequenceActor : public ALevelSequenceActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) 
	void PlayERSequence();

};
