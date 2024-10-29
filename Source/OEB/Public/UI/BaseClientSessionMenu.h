// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "BaseClientSessionMenu.generated.h"

USTRUCT(BlueprintType)
struct FSessionInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FString SessionName;

	UPROPERTY(BlueprintReadOnly)
	FString HostName;

	UPROPERTY(BlueprintReadOnly)
	FString ServerName;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentPlayers;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxPlayers;
};

USTRUCT(BlueprintType)
struct FCreateSessionInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FName SessionName;
	UPROPERTY(BlueprintReadWrite)
		FName HostName;
	UPROPERTY(BlueprintReadWrite)
		bool bAllowJoinInProgress;
	UPROPERTY(BlueprintReadWrite)
		bool bIsDedicated;
	UPROPERTY(BlueprintReadWrite)
		bool bShouldAdvertise;
	UPROPERTY(BlueprintReadWrite)
		bool bUsesPresence;
	UPROPERTY(BlueprintReadWrite)
		int NumPublicConnections;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSessionInteractDelegate, FSessionInfo, SessionInfo);
/**
 * 
 */
UCLASS()
class OEB_API UBaseClientSessionMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual bool Initialize() override;
	
	UPROPERTY(BlueprintAssignable)
	FSessionInteractDelegate OnSessionFound;

	UFUNCTION(BlueprintCallable)
	void CreateSession(FCreateSessionInfo CreateSessionInfo) const;

	UFUNCTION(BlueprintCallable)
	void FindSessions(int MaxSearchResults = 10000, bool bIsLanQuery = false);

	UFUNCTION(BlueprintCallable)
	void JoinSession(FName SessionName);

	UPROPERTY(EditDefaultsOnly)
	bool bShouldDestroySessionOnEnd;

	virtual void BeginDestroy() override;
protected:
	
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	virtual void OnCreateSessionComplete(FName SessionName, bool bSucceeded) const;
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) const;
	virtual void OnFindSessionsComplete(bool bSucceeded) const;

private:

	class UOEBGameInstance* GameInstance;

	const FName K_ServerNameKey = "SERVER_NAME_KEY";
	const FName K_HostNameKey = "SERVER_HOSTNAME_KEY";
};
