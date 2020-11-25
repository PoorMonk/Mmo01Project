// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectRoomWidget.h"
#include "RoomItemWidget.h"
#include "Center/MmoGameInstance.h"
#include "HFCommon.h"

void USelectRoomWidget::OnLeftBtnClicked()
{
	currRoom--;
	if (currRoom < 0)
	{
		currRoom = RoomList.Num() - 1;
	}
	UMG_RoomItem->ShowUI(currRoom);
}

void USelectRoomWidget::OnRightBtnClicked()
{
	currRoom++;
	if (currRoom >= RoomList.Num())
	{
		currRoom = 0;
	}
	UMG_RoomItem->ShowUI(currRoom);
}

void USelectRoomWidget::OnConfirmBtnClicked()
{
	UKBEventData_SelectRoom* EventData = NewObject<UKBEventData_SelectRoom>();
	EventData->RoomID = RoomList[currRoom].RoomId;
	KBENGINE_EVENT_FIRE("SelectRoom", EventData);
}
