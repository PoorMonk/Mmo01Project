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
	//�������ñ�ģ���Լ���ģ���EditChangeModuleType����
	void IterChangeModuleType(UHFModule* Module, FName ModType);
	//�ݹ鴴��ģ��
	void IterCreateManager(UHFModule* Module);
	//�ݹ��ʼ��
	void IterModuleInit(UHFModule* Module);
	//�ݹ�BeginPlay
	void IterModuleBeginPlay(UHFModule* Module);
	//�ݹ�Tick
	void IterModuleTick(UHFModule* Module, float DeltaSeconds);

	//��ȡ����ģ�鵽����
	void TotalGatherModule(FName ModType);
	
	void IterGatherModule(UHFModule* Module, TArray<UHFModule*>& GatherGrooup);

	bool RegisterToModule(IHFOOInterface* Obj);

	//ִ�з��䷽��
	void AllowExecuteFunction(HFModuleAgreement Agreement, HFParam* Param);
	void AllowExecuteFunction(HFObjectAgreement Agreement, HFParam* Param);

	//ע����÷���
	template<typename RetType, typename... VarTypes>
	HFFuncHandle AllotRegisterFuncPort(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InsFunc);

protected:
	//����ģ������飬˳����ö����ͬ
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