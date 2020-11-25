// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFCore/HFModule.h"
#include "HFCenterModule.generated.h"

class IHFOOInterface;

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFCenterModule : public UHFModule
{
	GENERATED_BODY()
	
public:
	//迭代调用本模组以及子模组的EditChangeModuleType方法
	void IterChangeModuleType(UHFModule* Module, FName ModType);
	//递归创建模块
	void IterCreateManager(UHFModule* Module);
	//递归初始化
	void IterModuleInit(UHFModule* Module);
	//递归BeginPlay
	void IterModuleBeginPlay(UHFModule* Module);
	//递归Tick
	void IterModuleTick(UHFModule* Module, float DeltaSeconds);

	//提取所有模组到数组
	void TotalGatherModule(FName ModType);
	
	void IterGatherModule(UHFModule* Module, TArray<UHFModule*>& GatherGrooup);

	bool RegisterToModule(IHFOOInterface* Obj);

	//执行反射方法
	void AllowExecuteFunction(HFModuleAgreement Agreement, HFParam* Param);
	void AllowExecuteFunction(HFObjectAgreement Agreement, HFParam* Param);

	//注册调用方法
	template<typename RetType, typename... VarTypes>
	HFFuncHandle AllotRegisterFuncPort(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InsFunc);

protected:
	//保存模组的数组，顺序与枚举相同
	TArray<UHFModule*> ModuleGroup;
};

template<typename RetType, typename... VarTypes>
HFFuncHandle UHFCenterModule::AllotRegisterFuncPort(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InsFunc)
{
	if (ModuleGroup[ModuleID])
	{
		return ModuleGroup[ModuleID]->RegisterFuncPort<RetType, VarTypes...>(CallName, InsFunc);
	}
	return HFFuncHandle();
}
