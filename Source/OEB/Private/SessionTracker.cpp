// Fill out your copyright notice in the Description page of Project Settings.

#include "SessionTracker.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

bool USessionTracker::TrackSessionName(const FName NewSession)
{
	if(!SessionsInitialized.Contains(NewSession))
	{
		SessionsInitialized.Add(NewSession);
		return true;
	}
	
	return false;
}

void USessionTracker::BeginDestroy()
{
	Super::BeginDestroy();
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		if (IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface())
		{
			if (SessionInterface.IsValid())
			{
				for(const FName& SessionName : SessionsInitialized)
				{
					SessionInterface->DestroySession(SessionName);
				}				
			}
		}
	}
	
	Super::BeginDestroy();
}
