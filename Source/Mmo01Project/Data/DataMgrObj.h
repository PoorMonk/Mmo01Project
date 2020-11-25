// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataMgrObj.generated.h"

class URoleDataAsset;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API UDataMgrObj : public UObject
{
	GENERATED_BODY()

public:
	
	static UDataMgrObj* Get();

	void LoadRoleData();

	// 获取数据函数
	UTexture* GetRoleTexture(int32 InIndex);

protected:
	UPROPERTY()
	URoleDataAsset* RoleData;

	static UDataMgrObj* MgrInst;
};
