// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFMMInterface.h"
#include "Engine/StreamableManager.h"
#include "HFWealth.generated.h"

//����Object�ڵ�
struct ObjectSingleLoadNode;
struct ObjectKindLoadNode;

struct ClassSingleLoadNode;
struct ClassKindLoadNode;
struct ClassMultiLoadNode;

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFWealth : public UObject, public IHFMMInterface
{
	GENERATED_BODY()
	
public:

	virtual void WealthInit() {}
	virtual void WealthBeginPlay();
	virtual void WealthTick(float DeltaSeconds);
	
	//ָ����Դ��
	void AssignData(TArray<UWealthData*>& InWealthData);

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
	void BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName ObjectName,
		FName FuncName, TArray<FTransform> SpawnTransforms);

protected:
	//����Object����ص�����
	HFOBJFUNC_TWO(BackCallObjWealth, FName, BackCallName, UObject*, BackCallWealth);
	HFOBJFUNC_TWO(BackCallObjWealthKind, TArray<FName>, BackCallNames, TArray<UObject*>, BackCallWealths);

	HFOBJFUNC_TWO(BackCallClassWealth, FName, BackCallName, UClass*, BackCallWealth);
	HFOBJFUNC_TWO(BackCallClassWealthKind, TArray<FName>, BackCallNames, TArray<UClass*>, BackCallWealths);

	HFOBJFUNC_TWO(BackCallObjectSingle, FName, BackCallName, UObject*, BackCallObject);
	HFOBJFUNC_TWO(BackCallObjectKind, TArray<FName>, BackCallName, TArray<UObject*>, BackCallObjects);
	HFOBJFUNC_TWO(BackCallObjectMulti, FName, BackCallName, TArray<UObject*>, BackCallObject);

	HFOBJFUNC_TWO(BackCallActorSingle, FName, BackCallName, AActor*, BackCallActor);
	HFOBJFUNC_TWO(BackCallActorKind, TArray<FName>, BackCallNames, TArray<AActor*>, BackCallActors);
	HFOBJFUNC_TWO(BackCallActorMulti, FName, BackCallNames, TArray<AActor*>, BackCallActors);

	HFOBJFUNC_TWO(BackCallWidgetSingle, FName, BackCallName, UUserWidget*, BackCallWidget);
	HFOBJFUNC_TWO(BackCallWidgetKind, TArray<FName>, BackCallNames, TArray<UUserWidget*>, BackCallWidgets);
	HFOBJFUNC_TWO(BackCallWidgetMulti, FName, BackCallNames, TArray<UUserWidget*>, BackCallWidgets);

	//��ȡObject��Դ�ṹ��
	FObjectWealthEntry* GetSingleObjEntry(FName WealthName);
	TArray<FObjectWealthEntry*> GetKindObjEntry(FName WealthKind);

	//��ȡClass��Դ�ṹ��
	FClassWealthEntry* GetSingleClassEntry(FName WealthName);
	TArray<FClassWealthEntry*> GetKindClassEntry(FName WealthKind);

	//������ص���Object�ڵ�ķ���
	void DealSingleObjLoadStack();
	//������������Object�ڵ�ķ���
	void DealKindObjectLoadStack();
	//������ص���Class�ڵ�ķ���
	void DealSingleClassLoadStack();
	//�����������Class�ڵ�ķ���
	void DealKindClassLoadStack();
	//�������������ķ���
	void DealMultiClassLoadStack();

protected:
	TArray<UWealthData*> WealthData;

	UPROPERTY()
		TArray<class UUserWidget*> GCWidgetGroup;

	//������
	FStreamableManager WealthLoader;

	//���ؽڵ����
	TArray<ObjectSingleLoadNode*> ObjectSingleLoadStack;
	TArray<ObjectKindLoadNode*> ObjectKindLoadStack;

	TArray<ClassSingleLoadNode*> ClassSingleLoadStack;
	TArray<ClassKindLoadNode*> ClassKindLoadStack;
	TArray<ClassMultiLoadNode*> ClassMultiLoadStack;
};
