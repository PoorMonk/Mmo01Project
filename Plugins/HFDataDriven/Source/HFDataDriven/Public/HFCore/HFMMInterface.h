// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HFCommon/HFCommon.h"

#include "HFMMInterface.generated.h"

class UHFModule;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHFMMInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HFDATADRIVEN_API IHFMMInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//指定模组
	void AssignModule(UHFModule* Mod);

protected:

	//执行反射方法
	void ExecuteFunction(HFModuleAgreement Agreement, HFParam* Param);
	void ExecuteFunction(HFObjectAgreement Agreement, HFParam* Param);

	UWorld* GetHFWorld() const;

protected:
	//保存对应的模组
	UHFModule* IModule;

	//保存对应的驱动器
	AHFDriver* IDriver;

	//对应模组的序号
	int32 ModuleIndex;
};
