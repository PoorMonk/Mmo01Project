// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HFMessage.h"
#include "HFModule.generated.h"

class UHFModel;
class UHFWealth;
class IHFOOInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HFDATADRIVEN_API UHFModule : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHFModule();

	void CreateManager();

	virtual void ModuleInit();

	virtual void ModuleBeginPlay();

	virtual void ModuleTick(float DeltaSeconds);

	void ChangeModuleType(FName ModuleType);

	//ע���������ģ��
	void RegisterObject(IHFOOInterface* ObjectInst);

	//ģ�������������
	void ChildDestroy(FName ObjectName);

	//��ʱ���Է���
	/*UFUNCTION()
		void TestReflect(int32 Counter, FString InfoStr, bool& BackResult);

	UFUNCTION()
		void TestNoParam();*/

	//�����¼��������ٶ���
	UFUNCTION()
		void DestroyObject(EAgreementType Agreement, TArray<FName> TargetNameGroup);

	//�����¼������������
	UFUNCTION()
		void EnableObject(EAgreementType Agreement, TArray<FName> TargetNameGroup);

	//�����¼�����ʧ�����
	UFUNCTION()
		void DisableObject(EAgreementType Agreement, TArray<FName> TargetNameGroup);

	//����ģ�鷽��
	void ExecuteFunction(HFModuleAgreement Agreement, HFParam* Param);

	//���ö��󷽷�
	void ExecuteFunction(HFObjectAgreement Agreement, HFParam* Param);

	//ע����ýӿ�
	template<typename RetType, typename... VarTypes>
	HFCallHandle<RetType, VarTypes...> RegisterCallPort(FName CallName);

	//ע�᷽���ӿ�
	template<typename RetType, typename... VarTypes>
	HFFuncHandle RegisterFuncPort(FName CallName, TFunction<RetType(VarTypes...)> InsFunc);

	//�ⲿ����������ȡ��Դ����
	FWealthURL* GainWealthURL(FName WealthName);
	void GainWealthURL(FName WealthKind, TArray<FWealthURL*>& OutURL);

	//����Object������Դ�ӿ�
	void LoadObjectWealth(FName WealthName, FName ObjectName, FName FuncName);
	void LoadObjectWealthKind(FName WealthKind, FName ObjectName, FName FuncName);

	//����UClass������Դ�ӿ�
	void LoadUClassWealth(FName WealthName, FName ObjectName, FName FuncName);
	void LoadUClassWealthKind(FName WealthKind, FName ObjectName, FName FuncName);

	//����һ������ʵ��
	void BuildSingleClassWealth(EWealthType WealthType, FName WealthName, FName ObjectName,
		FName FuncName, FTransform SpawnTransform);

	//����ͬ��Դ�������Ķ���ʵ����ͬ�������µ�ÿ����Դ���Ӵ���һ������ʵ��
	void BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName ObjectName,
		FName FuncName, TArray<FTransform> SpawnTransforms);

	//�������ͬ��Դ���Ķ���ʵ��
	void BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amout, FName ObjectName,
		FName FuncName, TArray<FTransform> SpawnTransforms);

public:
	UPROPERTY(EditAnywhere, Category = "HFDataDriven")
		TArray<UWealthData*> WealthData;

	TArray<UHFModule*> ChildrenModules;

	int32 ModuleIndex;

protected:

	//ִ�е������󷽷�
	void ExecuteSelfObject(HFObjectAgreement Agreement, HFParam* Param);
	//ִ����������ķ���
	void ExecuteOtherObject(HFObjectAgreement Agreement, HFParam* Param);
	//ִ����ͬ���������󷽷�
	void ExecuteClassOtherObject(HFObjectAgreement Agreement, HFParam* Param);
	//ִ�������ķ���
	void ExecuteSelfClass(HFObjectAgreement Agreement, HFParam* Param);
	//ִ�����������ķ���
	void ExecuteOtherClass(HFObjectAgreement Agreement, HFParam* Param);
	//ִ�����ж���ķ���
	void ExecuteAll(HFObjectAgreement Agreement, HFParam* Param);


protected:
	//����ģ��ָ��
	UHFModel* Model;
	//��Ϣģ��ָ��
	UHFMessage* Message;
	//��Դģ��ָ��
	UHFWealth* Wealth;

private:
	void ExecuteFunc(const TArray<IHFOOInterface*>& TargetObjGroup, HFObjectAgreement Agreement, HFParam* Param);
};

template<typename RetType, typename... VarTypes>
HFCallHandle<RetType, VarTypes...>
UHFModule::RegisterCallPort(FName CallName)
{
	return Message->RegisterCallPort<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename... VarTypes>
HFFuncHandle UHFModule::RegisterFuncPort(FName CallName, TFunction<RetType(VarTypes...)> InsFunc)
{
	return Message->RegisterFuncPort<RetType, VarTypes...>(CallName, InsFunc);
}
