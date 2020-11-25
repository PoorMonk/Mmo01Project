// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HFCore/HFModule.h"
#include "HFCore/HFDriver.h"
#include "HFOOInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHFOOInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HFDATADRIVEN_API IHFOOInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//ע�ᵽ���
	void RegisterToModule(FName ModName, FName ObjName = FName(), FName ClsName = FName());
	//ͨ��ģ��IDע��
	void RegisterToModule(int32 ModuleIndex, FName ObjName = FName(), FName ClsName = FName());
	//��ȡ������
	FName GetObjectName() const;
	//��ȡ����
	FName GetClassName() const;
	//��ȡģ��Index
	int32 GetModuleIndex() const;
	//��ȡObject����
	UObject* GetObjectBody() const;
	//��ܻ�ȡ���纯��
	UWorld* GetHFWorld() const;
	//���ⲿָ��ģ��
	void AssignModule(UHFModule* Mod);

	//������������
	bool ActiveLife();

	//�����������ں���
	bool DestroyLife();

	//�������ڣ���ģ�����������
	virtual void HFInit();		//��ʼ��
	virtual void HFLoading();	//���ذ󶨵���Դ
	virtual void HFRegister();	//ע�����ݻ��¼�
	virtual void HFEnable();	//�������

	virtual void HFTick(float DeltaSeconds);	//֡����

	virtual void HFDisable();	//ʧ�����
	virtual void HFUnRegister();//ע�����ݻ��¼�
	virtual void HFUnLoading();	//���ٰ���Դ
	virtual void HFRelease();	//�ͷ�

	//�������
	virtual void OnEnable();
	//ʧ�����
	virtual void OnDisable();
	//�����Լ�
	void HFDestroy();

public:
	//�Ƿ�����֡�������У�Ĭ��Ϊfalse
	bool IsAllowTickEvent;

	//��������
	EBaseObjectLife LifeState;

	//����״̬
	EBaseObjectState RunState;

protected:

	//ִ�з��䷽��
	void ExecuteFunction(HFModuleAgreement Agreement, HFParam* Param);
	void ExecuteFunction(HFObjectAgreement Agreement, HFParam* Param);

	//ע����ýӿ�
	template<typename RetType, typename... VarTypes>
	HFCallHandle<RetType, VarTypes...> RegisterCallPort(FName CallName);

	//ע�᷽���ӿ�
	template<typename RetType, typename... VarTypes>
	HFFuncHandle RegisterFuncPort(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InsFunc);

	//�ⲿ����������ȡ��Դ����
	FWealthURL* GainWealthURL(FName WealthName);
	void GainWealthURL(FName WealthKind, TArray<FWealthURL*>& OutURL);

	//����Object������Դ�ӿ�
	void LoadObjectWealth(FName WealthName, FName FuncName);
	void LoadObjectWealthKind(FName WealthKind, FName FuncName);

	//����UClass������Դ�ӿ�
	void LoadUClassWealth(FName WealthName, FName FuncName);
	void LoadUClassWealthKind(FName WealthKind, FName FuncName);

	//����һ������ʵ��
	void BuildSingleClassWealth(EWealthType WealthType, FName WealthName, FName FuncName);
	void BuildSingleClassWealth(EWealthType WealthType, FName WealthName, FName FuncName, FTransform SpawnTransform);

	//����ͬ��Դ�������Ķ���ʵ����ͬ�������µ�ÿ����Դ���Ӵ���һ������ʵ��
	void BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName FuncName);
	void BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName FuncName, FTransform SpawnTransforms);
	void BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName FuncName, TArray<FTransform> SpawnTransforms);

	//�������ͬ��Դ���Ķ���ʵ��
	void BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName FuncName);
	void BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName FuncName, FTransform SpawnTransform);
	void BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName FuncName, TArray<FTransform> SpawnTransforms);

protected:
	//���������UObject
	UObject* IBody;

	//����ģ��
	UHFModule* IModule;

	//����������
	AHFDriver* IDriver;

	//��������
	FName IObjectName;

	//����������
	FName IClassName;

	//��Ӧģ������
	int32 ModuleIndex;

private:
	void RegisterInit(FName ObjName = FName(), FName ClsName = FName());
	void Register(int32 ModIndex);
};

template<typename RetType, typename... VarTypes>
HFCallHandle<RetType, VarTypes...>
IHFOOInterface::RegisterCallPort(FName CallName)
{
	return IModule->RegisterCallPort<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename... VarTypes>
HFFuncHandle IHFOOInterface::RegisterFuncPort(int32 ModuleID, FName CallName, TFunction<RetType(VarTypes...)> InsFunc)
{
	if (ModuleID == ModuleIndex)
	{
		return IModule->RegisterFuncPort<RetType, VarTypes...>(CallName, InsFunc);
	}
	else
	{
		return IDriver->RegisterFuncPort<RetType, VarTypes...>(ModuleID, CallName, InsFunc);
	}
}
