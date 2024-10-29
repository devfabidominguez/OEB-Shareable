// Fill out your copyright notice in the Description page of Project Settings.


#include "WaypointsRegistryInfo.h"

AActor* FAIWaypointRegistry::GetNextWaypoint()
{
	AActor* NextWaypoint = nullptr;
	if (CurrentIndex > Waypoints.Num() - 1)
	{
		if (bLoopGetWaypoint)
		{
			CurrentIndex = 0;
		}
		else
		{
			return NextWaypoint;
		}
	}

	if (Waypoints.Num() - 1 >= CurrentIndex)
	{
		NextWaypoint = Waypoints[CurrentIndex];
	}	

	++CurrentIndex;

	return NextWaypoint;
}

int AWaypointsRegistryInfo::GetWaypointNum(const ACharacter* InCharacter) 
{
	if (!InCharacter)
	{
		return INDEX_NONE;
	}

	for (FAIWaypointRegistry& IteratedRegistry : Registry)
	{
		if (IteratedRegistry.Character == InCharacter)
		{
			return IteratedRegistry.Waypoints.Num();
		}
	}

	return INDEX_NONE;
}

AActor* AWaypointsRegistryInfo::GetRegistryNextWaypoint(const ACharacter* InCharacter)
{
	if (!InCharacter)
	{
		return nullptr;
	}

	for (FAIWaypointRegistry& IteratedRegistry : Registry)
	{
		if (IteratedRegistry.Character == InCharacter)
		{
			return IteratedRegistry.GetNextWaypoint();
		}
	}

	return nullptr;
}