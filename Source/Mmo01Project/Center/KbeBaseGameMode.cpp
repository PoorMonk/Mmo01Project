// Fill out your copyright notice in the Description page of Project Settings.


#include "KbeBaseGameMode.h"
#include "KBEnginePlugins/Engine/KBEvent.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "HFDataDriven/Public/HFCommon/HFCommon.h"
#include "TimerManager.h"
#include "Engine/World.h"

AKbeBaseGameMode::AKbeBaseGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AKbeBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	InstallEvent();
}

void AKbeBaseGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnInstallEvent();
}

void AKbeBaseGameMode::InstallEvent()
{
	//注册最基本的回调事件
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);
}

void AKbeBaseGameMode::UnInstallEvent()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void AKbeBaseGameMode::OnKicked(const UKBEventData* EventData)
{
	const UKBEventData_onKicked* ServerData = Cast<UKBEventData_onKicked>(EventData);

	HFH::Debug() << "OnKicked: failedCode --> " << ServerData->failedcode << " ; errorStr --> " <<
		ServerData->errorStr << HFH::Endl();
}

void AKbeBaseGameMode::OnDisconnected(const UKBEventData* EventData)
{
	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(EventData);

	HFH::Debug() << "OnDisconnected: eventName --> " << ServerData->eventName << HFH::Endl();
}

void AKbeBaseGameMode::OnConnectionState(const UKBEventData* EventData)
{
	const UKBEventData_onConnectionState* ServerData = Cast<UKBEventData_onConnectionState>(EventData);

	HFH::Debug() << "OnConnectionState: success --> " << ServerData->success << " ; address --> " <<
		ServerData->address << HFH::Endl();

	if (!ServerData->success)
	{
		StartReloginBaseapp();
	}
}

void AKbeBaseGameMode::OnReloginBaseappSuccessfully(const UKBEventData* EventData)
{
	const UKBEventData_onReloginBaseappSuccessfully* ServerData = Cast<UKBEventData_onReloginBaseappSuccessfully>(EventData);

	HFH::Debug() << "OnReloginBaseappSuccessfully: eventName --> " << ServerData->eventName << HFH::Endl();

	StopReloginBaseapp();
}

void AKbeBaseGameMode::OnReloginBaseappFailed(const UKBEventData* EventData)
{
	const UKBEventData_onReloginBaseappFailed* ServerData = Cast<UKBEventData_onReloginBaseappFailed>(EventData);

	HFH::Debug() << "OnReloginBaseappFailed: failedCode --> " << ServerData->failedcode << " ; errorstr --> " <<
		ServerData->errorStr << HFH::Endl();
}

void AKbeBaseGameMode::StartReloginBaseapp()
{
	if (!ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(ReloginHandle, this, &AKbeBaseGameMode::OnReloginBaseapp, 1.f, true, 1.f);
	}
}

void AKbeBaseGameMode::StopReloginBaseapp()
{
	if (ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloginHandle);
	}
}

void AKbeBaseGameMode::OnReloginBaseapp()
{
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();
}
