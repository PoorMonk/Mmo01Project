// Fill out your copyright notice in the Description page of Project Settings.


#include "DataMgrObj.h"
#include "RoleDataAsset.h"

UDataMgrObj* UDataMgrObj::MgrInst = nullptr;

UDataMgrObj* UDataMgrObj::Get()
{
	if (MgrInst == nullptr)
	{
		MgrInst = NewObject<UDataMgrObj>();
		MgrInst->AddToRoot();
		MgrInst->LoadRoleData();
	}

	return MgrInst;
}

void UDataMgrObj::LoadRoleData()
{
	RoleData = LoadObject<URoleDataAsset>(nullptr, TEXT("RoleDataAsset'/Game/Blueprints/Data/BP_RoleData.BP_RoleData'"));
}

UTexture* UDataMgrObj::GetRoleTexture(int32 InIndex)
{
	return RoleData->RoleTextures[InIndex];
}
