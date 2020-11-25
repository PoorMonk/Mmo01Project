// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectRoomGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/MmoEventData.h"
#include "HUD/SelectRoomWidget.h"
#include "Kismet/GameplayStatics.h"

void ASelectRoomGameMode::InstallEvent()
{
	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT("OnReqRoomList", OnReqRoomList);
	KBENGINE_REGISTER_EVENT("OnSelectRoom", OnSelectRoom);
}

void ASelectRoomGameMode::BeginPlay()
{
	SelRoomWidget = CreateWidget<USelectRoomWidget>(GetWorld(), SelectRoomClass);
	SelRoomWidget->SelRoomGameMode = this;
	SelRoomWidget->AddToViewport();

	Super::BeginPlay();

	KBENGINE_EVENT_FIRE("ReqRoomList", NewObject<UKBEventData>());
}

void ASelectRoomGameMode::OnReqRoomList(const UKBEventData* pEventData)
{
	const UKBEventData_OnReqRoomList* ServerData = Cast<UKBEventData_OnReqRoomList>(pEventData);
	SelRoomWidget->RoomList = ServerData->RoomList;
}

void ASelectRoomGameMode::OnSelectRoom(const UKBEventData* pEventData)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("RoleMap"));
}
