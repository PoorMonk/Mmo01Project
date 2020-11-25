// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFMMInterface.h"
#include "Engine/StreamableManager.h"
#include "HFWealth.generated.h"

//加载Object节点
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
	
	//指定资源组
	void AssignData(TArray<UWealthData*>& InWealthData);

	//外部方法单纯获取资源链接
	FWealthURL* GainWealthURL(FName WealthName);
	void GainWealthURL(FName WealthKind, TArray<FWealthURL*>& OutURL);

	//加载Object类型资源接口
	void LoadObjectWealth(FName WealthName, FName ObjectName, FName FuncName);
	void LoadObjectWealthKind(FName WealthKind, FName ObjectName, FName FuncName);

	//加载UClass类型资源接口
	void LoadUClassWealth(FName WealthName, FName ObjectName, FName FuncName);
	void LoadUClassWealthKind(FName WealthKind, FName ObjectName, FName FuncName);

	//创建一个对象实例
	void BuildSingleClassWealth(EWealthType WealthType, FName WealthName, FName ObjectName,
		FName FuncName, FTransform SpawnTransform);

	//创建同资源种类名的对象实例，同种类名下的每个资源链接创建一个对象实例
	void BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName ObjectName,
		FName FuncName, TArray<FTransform> SpawnTransforms);

	//创建多个同资源名的对象实例
	void BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName ObjectName,
		FName FuncName, TArray<FTransform> SpawnTransforms);

protected:
	//加载Object反射回调函数
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

	//获取Object资源结构体
	FObjectWealthEntry* GetSingleObjEntry(FName WealthName);
	TArray<FObjectWealthEntry*> GetKindObjEntry(FName WealthKind);

	//获取Class资源结构体
	FClassWealthEntry* GetSingleClassEntry(FName WealthName);
	TArray<FClassWealthEntry*> GetKindClassEntry(FName WealthKind);

	//处理加载单个Object节点的方法
	void DealSingleObjLoadStack();
	//处理批量加载Object节点的方法
	void DealKindObjectLoadStack();
	//处理加载单个Class节点的方法
	void DealSingleClassLoadStack();
	//处理加载批量Class节点的方法
	void DealKindClassLoadStack();
	//处理创建多个对象的方法
	void DealMultiClassLoadStack();

protected:
	TArray<UWealthData*> WealthData;

	UPROPERTY()
		TArray<class UUserWidget*> GCWidgetGroup;

	//加载器
	FStreamableManager WealthLoader;

	//加载节点队列
	TArray<ObjectSingleLoadNode*> ObjectSingleLoadStack;
	TArray<ObjectKindLoadNode*> ObjectKindLoadStack;

	TArray<ClassSingleLoadNode*> ClassSingleLoadStack;
	TArray<ClassKindLoadNode*> ClassKindLoadStack;
	TArray<ClassMultiLoadNode*> ClassMultiLoadStack;
};
