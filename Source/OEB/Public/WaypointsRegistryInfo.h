// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "WaypointsRegistryInfo.generated.h"


USTRUCT(Blueprintable)
struct OEB_API FAIWaypointRegistry
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> Waypoints;
	
	UPROPERTY(EditAnywhere)
	ACharacter* Character;

	UPROPERTY(EditAnywhere)
	bool bLoopGetWaypoint;

	AActor* GetNextWaypoint();	

private: 
	int CurrentIndex = 0;
};
/**
 * 
 */
UCLASS(Blueprintable)
class OEB_API AWaypointsRegistryInfo : public AInfo
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	AActor* GetRegistryNextWaypoint(const ACharacter* InCharacter);

	UFUNCTION(BlueprintCallable)
	int GetWaypointNum(const ACharacter* InCharacter);

	UPROPERTY(EditAnywhere)
	TArray<FAIWaypointRegistry> Registry;
};
