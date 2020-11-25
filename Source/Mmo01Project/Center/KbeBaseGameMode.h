// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KbeBaseGameMode.generated.h"

class UKBEventData;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API AKbeBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AKbeBaseGameMode();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InstallEvent();
	virtual void UnInstallEvent();

	virtual void OnKicked(const UKBEventData* EventData);
	virtual void OnDisconnected(const UKBEventData* EventData);
	virtual void OnConnectionState(const UKBEventData* EventData);
	virtual void OnReloginBaseappSuccessfully(const UKBEventData* EventData);
	virtual void OnReloginBaseappFailed(const UKBEventData* EventData);

	void StartReloginBaseapp();
	void StopReloginBaseapp();

	// 重连定时器事件
	void OnReloginBaseapp();

protected:

	FTimerHandle ReloginHandle;

};
