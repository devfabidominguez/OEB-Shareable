// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SessionTracker.generated.h"

/**
 * 
 */
UCLASS()
class OEB_API USessionTracker : public UObject
{
	GENERATED_BODY()

public:
	bool TrackSessionName(FName NewSession);
protected:
	virtual void BeginDestroy() override;
private:
	UPROPERTY(Transient)
	TArray<FName> SessionsInitialized;
};
