// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameMode.h"
#include "HUD/LoginWidget.h"
#include "KbeClientActor.h"
#include "EngineUtils.h"
#include "KBEnginePlugins/Engine/KBEMain.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "KBEnginePlugins/Engine/KBEvent.h"
#include "HFDataDriven/Public/HFCommon/HFCommon.h"

void ALoginGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (LoginWidgetClass)
	{
		MmoLoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
		MmoLoginWidget->MmoLoginGameMode = this;
		MmoLoginWidget->AddToViewport();
	}

	for (TActorIterator<AKbeClientActor> ActItem(GetWorld()); ActItem; ++ActItem)
	{
		KbeMain = (*ActItem)->KbeMain;
	}
}

void ALoginGameMode::InstallEvent()
{
	// ÿ�ν��뵽��¼����������һ��KBE������KBE�����������һֱ����
	KBEngine::KBEngineApp::getSingleton().reset();

	Super::InstallEvent();

	//�����û����ʵ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	//��½ʧ�ܻص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	//�汾ƥ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	//�汾��ƥ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	//��½baseappʧ�ܻص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	//��½baseapp�ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	//��½�ɹ��ص�, ����ExAccount����__init__()ʱ����, ��������ת��ѡ���ɫ����
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);
}

void ALoginGameMode::UnInstallEvent()
{
	Super::UnInstallEvent();
}

void ALoginGameMode::OnCreateAccountResult(const UKBEventData* pEventData)
{
	const UKBEventData_onCreateAccountResult* ServerData = Cast<UKBEventData_onCreateAccountResult>(pEventData);
	//HFH::Debug() << "OnCreateAccountResult : errorCode --> " << ServerData->errorCode << " ; errorStr --> " << ServerData->errorStr << HFH::Endl();
}

void ALoginGameMode::OnLoginFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginFailed* ServerData = Cast<UKBEventData_onLoginFailed>(pEventData);

	//HFH::Debug() << "OnLoginFailed : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << HFH::Endl();
}

void ALoginGameMode::OnVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onVersionNotMatch* ServerData = Cast<UKBEventData_onVersionNotMatch>(pEventData);

	//HFH::Debug() << "OnVersionNotMatch : clientVersion --> " << ServerData->clientVersion << " ; serverVersion --> " << ServerData->serverVersion << HFH::Endl();
}

void ALoginGameMode::OnScriptVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onScriptVersionNotMatch* ServerData = Cast<UKBEventData_onScriptVersionNotMatch>(pEventData);

	//HFH::Debug() << "OnScriptVersionNotMatch : clientScriptVersion --> " << ServerData->clientScriptVersion << " ; serverScriptVersion --> " << HFH::Endl();
}

void ALoginGameMode::OnLoginBaseappFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseappFailed* ServerData = Cast<UKBEventData_onLoginBaseappFailed>(pEventData);

	//HFH::Debug() << "OnLoginBaseappFailed : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << HFH::Endl();
}

void ALoginGameMode::OnLoginBaseapp(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseapp* ServerData = Cast<UKBEventData_onLoginBaseapp>(pEventData);

	//HFH::Debug() << "OnLoginBaseapp : eventName --> " << ServerData->eventName << HFH::Endl();
}

void ALoginGameMode::OnLoginSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginSuccessfully* ServerData = Cast<UKBEventData_onLoginSuccessfully>(pEventData);

	//HFH::Debug() << "OnLoginSuccessfully : entity_uuid --> " << ServerData->entity_uuid << " ; entity_id --> " << ServerData->entity_id << HFH::Endl();

	UGameplayStatics::OpenLevel(GetWorld(), FName("RoomMap"));
}
