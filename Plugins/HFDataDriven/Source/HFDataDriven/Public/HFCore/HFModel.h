// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HFMMInterface.h"
#include "HFModel.generated.h"

class IHFOOInterface;

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFModel : public UObject, public IHFMMInterface
{
	GENERATED_BODY()
	
public:

	virtual void ModelInit() {}
	virtual void ModelBeginPlay() {}
	virtual void ModelTick(float DeltaSeconds);

	//注册对象到数据模块
	void RegisterObject(IHFOOInterface* ObjectInst);

	//销毁对象
	void DestroyObject(FName ObjectName);

	//批量销毁对象
	void DestroyObject(EAgreementType Agreement, TArray<FName> TargetNameGroup);
	//批量激活对象
	void EnableObject(EAgreementType Agreement, TArray<FName> TargetNameGroup);
	//批量失活对象
	void DisableObject(EAgreementType Agreement, TArray<FName> TargetNameGroup);
	//根据传入的对象名获取对象
	void GetSelfObject(TArray<FName> TargetNameGroup, TArray<IHFOOInterface*>& TargetObjectGroup);
	//根据传入的对象名获取对象名外的其它对象
	int32 GetOtherObject(TArray<FName> TargetNameGroup, TArray<IHFOOInterface*>& TargetObjectGroup);
	//根据名字获取其它类的类型数量
	int32 GetClassOtherObject(TArray<FName> TargetNameGroup, TArray<IHFOOInterface*>& TargetObjectGroup);
	//根据名字获取类
	void GetSelfClass(TArray<FName> TargetNameGroup, TArray<IHFOOInterface*>& TargetObjectGroup);
	//根据名字获取其它类
	void GetOtherClass(TArray<FName> TargetNameGroup, TArray<IHFOOInterface*>& TargetObjectGroup);
	//获取所有对象
	void GetAll(TArray<IHFOOInterface*>& TargetObjectGroup);

	//根据协议获取对象集合
	void GetAgreementObject(EAgreementType Agreement, TArray<FName> TargetNameGroup, TArray<IHFOOInterface*>& TargetObjectGroup);

protected:
	//框架对象数组，key:ObjectName
	TMap<FName, IHFOOInterface*> ObjectGroup;

	//框架对象类集合，key:ClassName
	TMap<FName, TArray<IHFOOInterface*>> ObjectClassGroup;

	//等待生命周期的对象集
	TArray<IHFOOInterface*> ObjectActiveGroup;
	//需要运行Tick函数的对象集合
	TArray<IHFOOInterface*> ObjectTickGroup;
	//销毁生命周期的对象集
	TArray<IHFOOInterface*> ObjectDestroyGroup;
	//释放周期函数对象集合
	TArray<IHFOOInterface*> ObjectReleaseGroup;
	//预销毁对象（还处于激活状态，需要运行完才能销毁）
	TArray<IHFOOInterface*> PreObjectDestroyGroup;
};
