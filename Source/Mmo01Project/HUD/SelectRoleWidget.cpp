// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectRoleWidget.h"
#include "RoleItemWidget.h"
#include "Data/DataMgrObj.h"
#include "SizeBox.h"
#include "SizeBoxSlot.h"
#include "WidgetTree.h"
#include "HFCommon.h"
#include "Center/SelectRoleGameMode.h"
#include "Center/RoleRenderActor.h"
#include "TextBlock.h"

void USelectRoleWidget::InitRoleListUI()
{
	for (int i = 0; i < RoleList.Num(); ++i)
	{
		if (i >= 2) return;
		URoleItemWidget* RoleItem = WidgetTree->ConstructWidget<URoleItemWidget>(RoleItemClass); 
		RoleItem->InitWidget(RoleList[i].Name, (UTexture2D*)UDataMgrObj::Get()->GetRoleTexture(i));
		if (0 == i)
			RoleOneSizeBox->AddChild(RoleItem);
		else if (1 == i)
			RoleTwoSizeBox->AddChild(RoleItem);
		
		RoleItem->RoleClickedDele.BindUObject(this, &USelectRoleWidget::RoleItemClickedDele);
		RoleItemGroup.Add(RoleList[i].Name, RoleItem);
	}
}

void USelectRoleWidget::RoleItemClickedDele(FString RoleName)
{
	for (auto RoleInfo : RoleList)
	{
		if (RoleInfo.Name == RoleName)
		{
			Dbid = RoleInfo.Dbid;
		}
	}
	for (TPair<FString, URoleItemWidget*>& element : RoleItemGroup) 
	{		
		element.Value->ShowMask(RoleName.Equals(element.Key));		
	}

	Text_RoleName->SetText(FText::FromString(RoleName));
	if (RoleName == "Veigar")
	{
		MmoSelectRoleGamemode->RoleRenderActor->SwitchRoleMesh(1);
	}
	else
	{
		MmoSelectRoleGamemode->RoleRenderActor->SwitchRoleMesh(0);
	}
}

void USelectRoleWidget::OnEnterGameBtnClicked()
{
	UKBEventData_ReqSelectRole* EventData = NewObject<UKBEventData_ReqSelectRole>();
	EventData->DbID = Dbid;
	KBENGINE_EVENT_FIRE("ReqSelectRole", EventData);
}
