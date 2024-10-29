// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseClientSessionMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"
#include "../OEBGameInstance.h"
#include "SessionTracker.h"

void UBaseClientSessionMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UBaseClientSessionMenu::OnFindSessionsComplete);
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UBaseClientSessionMenu::OnCreateSessionComplete);
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UBaseClientSessionMenu::OnJoinSessionComplete);
	}
}

bool UBaseClientSessionMenu::Initialize()
{	
	GameInstance = Cast<UOEBGameInstance>(GetGameInstance());
	return Super::Initialize();
}	

void UBaseClientSessionMenu::BeginDestroy()
{	
	if (SessionInterface.IsValid())
	{
		SessionInterface->OnFindSessionsCompleteDelegates.RemoveAll(this);
		SessionInterface->OnCreateSessionCompleteDelegates.RemoveAll(this);
		SessionInterface->OnJoinSessionCompleteDelegates.RemoveAll(this);		
	}
	Super::BeginDestroy();
}

void UBaseClientSessionMenu::CreateSession(FCreateSessionInfo CreateSessionInfo) const
{	
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = CreateSessionInfo.bAllowJoinInProgress;
	SessionSettings.bIsDedicated = CreateSessionInfo.bIsDedicated;
	SessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";	
	SessionSettings.bShouldAdvertise = CreateSessionInfo.bShouldAdvertise;
	SessionSettings.bUsesPresence = CreateSessionInfo.bUsesPresence;
	SessionSettings.NumPublicConnections = CreateSessionInfo.NumPublicConnections;
	
	SessionSettings.Set<FString>(K_ServerNameKey, CreateSessionInfo.SessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionSettings.Set<FString>(K_HostNameKey, CreateSessionInfo.HostName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	SessionInterface->CreateSession(0, CreateSessionInfo.SessionName, SessionSettings);
}

void UBaseClientSessionMenu::OnCreateSessionComplete(FName SessionName, bool bSucceeded) const
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, Succeded: %d"), bSucceeded);
	if (bSucceeded)
	{
		GameInstance->SessionTracker->TrackSessionName(SessionName);		
		
		if (GetWorld())
		{
			UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, ServerTravel"), bSucceeded);
			GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");
		}
	}
}

void UBaseClientSessionMenu::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) const
{
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete, SessionName %s"), *SessionName.ToString());
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress;
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "")
		{
			PlayerController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UBaseClientSessionMenu::OnFindSessionsComplete(bool bSucceeded) const
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete, Succeded: %d"), bSucceeded);
	if (bSucceeded)
	{
		if (SessionSearch.IsValid())
		{		
			for (const FOnlineSessionSearchResult Result : SessionSearch->SearchResults)
			{
				if (!Result.IsValid())
				{
					continue;
				}
				UE_LOG(LogTemp, Warning, TEXT("Joining Server"));
				FSessionInfo SessionInfo;
				SessionInfo.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
				SessionInfo.CurrentPlayers = SessionInfo.MaxPlayers - Result.Session.NumOpenPublicConnections;				
				
				Result.Session.SessionSettings.Get(K_ServerNameKey, SessionInfo.ServerName);
				Result.Session.SessionSettings.Get(K_HostNameKey, SessionInfo.HostName);
				SessionInfo.SessionName = SessionInfo.ServerName;
				OnSessionFound.Broadcast(SessionInfo);
			}
		}
	}
}

void UBaseClientSessionMenu::JoinSession(FName SessionName)
{
	if (SessionSearch.IsValid())
	{
		for (const FOnlineSessionSearchResult& SessionSearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Joining Server"));
			SessionInterface->JoinSession(0, SessionName, SessionSearchResult);
		};
	}	
}

void UBaseClientSessionMenu::FindSessions(int MaxSearchResults, bool bIsLanQuery)
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	SessionSearch->MaxSearchResults = MaxSearchResults;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}
