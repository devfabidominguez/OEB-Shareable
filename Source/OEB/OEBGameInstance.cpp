// Fill out your copyright notice in the Description page of Project Settings.

#include "OEBGameInstance.h"
#include "OEBCharacter.h"
#include "SessionTracker.h"

UOEBGameInstance::UOEBGameInstance()
{

}

void UOEBGameInstance::Init()
{
	SessionTracker = NewObject<USessionTracker>();
	//if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	//{
	//	SessionInterface = Subsystem->GetSessionInterface();
	//	if (SessionInterface.IsValid())
	//	{
	//		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGameInstance_PIR::OnCreateSessionComplete);
	//		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UGameInstance_PIR::OnFindSessionsComplete);
	//		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UGameInstance_PIR::OnJoinSessionComplete);
	//	}
	//}
	//
}

void UOEBGameInstance::LoadConfigFromBackend(FString ConfigID, bool bRefreshInstances)
{
}

void UOEBGameInstance::Shutdown()
{
	Super::Shutdown();
	
}
