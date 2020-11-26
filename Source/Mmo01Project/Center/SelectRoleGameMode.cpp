// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectRoleGameMode.h"
#include "HUD/SelectRoleWidget.h"
#include "Engine/KBEngine.h"
#include "Scripts/MmoEventData.h"
#include "Kismet/GameplayStatics.h"
#include "HFCommon.h"
#include "RoleRenderActor.h"
#include "EngineUtils.h"

void ASelectRoleGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ARoleRenderActor> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		RoleRenderActor = Cast<ARoleRenderActor>(*ActorIt);
	}

	MmoSelectRoleWidget = CreateWidget<USelectRoleWidget>(GetWorld(), SelectRoleClass);
	MmoSelectRoleWidget->MmoSelectRoleGamemode = this;
	MmoSelectRoleWidget->AddToViewport();

	KBENGINE_EVENT_FIRE("ReqRoleList", NewObject<UKBEventData>());
}

void ASelectRoleGameMode::AddSpaceGeometryMapping(const UKBEventData* EventData)
{
	const UKBEventData_addSpaceGeometryMapping* ServerData = Cast<UKBEventData_addSpaceGeometryMapping>(EventData);

	FString MapName;
	FString TempStr;
	ServerData->spaceResPath.Split("/", &TempStr, &MapName);
	HFH::Debug() << "Room MapName: " << MapName << HFH::Endl();

	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
}

void ASelectRoleGameMode::OnReqRoleList(const UKBEventData* pEventData)
{
	const UKBEventData_OnReqRoleList* ServerData = Cast<UKBEventData_OnReqRoleList>(pEventData);
	MmoSelectRoleWidget->RoleList = ServerData->RoleList;

	MmoSelectRoleWidget->InitRoleListUI();

	// 默认显示第一个
	if (MmoSelectRoleWidget->RoleList.Num() > 0)
	{
		MmoSelectRoleWidget->RoleItemClickedDele(MmoSelectRoleWidget->RoleList[0].Name);
	}
}

void ASelectRoleGameMode::OnSelectRole(const UKBEventData* pEventData)
{

}

void ASelectRoleGameMode::InstallEvent()
{
	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT("OnReqRoleList", OnReqRoleList);
	KBENGINE_REGISTER_EVENT("OnSelectRole", OnSelectRole);

	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", AddSpaceGeometryMapping);
}

void ASelectRoleGameMode::UnInstallEvent()
{
	Super::UnInstallEvent();
}


