// Fill out your copyright notice in the Description page of Project Settings.


#include "HFCore/HFWealth.h"
#include "HFObject/HFOOInterface.h"
#include "Blueprint/UserWidget.h"

struct ObjectSingleLoadNode
{
	//加载句柄
	TSharedPtr<FStreamableHandle> WealthHandle;
	//资源结构体
	FObjectWealthEntry* WealthEntry;
	//目标对象
	FName ObjectName;
	//回调方法名
	FName FuncName;

	ObjectSingleLoadNode(TSharedPtr<FStreamableHandle> InWealthHandle, FObjectWealthEntry* InWealthEntry, 
		FName InObjectName, FName InFuncName)
	{
		WealthHandle = InWealthHandle;
		WealthEntry = InWealthEntry;
		ObjectName = InObjectName;
		FuncName = InFuncName;
	}
};

struct ObjectKindLoadNode
{
	//加载句柄
	TSharedPtr<FStreamableHandle> WealthHandle;
	//已经加载的资源
	TArray<FObjectWealthEntry*> LoadedWealthEntry;
	//没有加载的资源
	TArray<FObjectWealthEntry*> UnLoadWealthEntry;
	//目标对象
	FName ObjectName;
	//回调方法名
	FName FuncName;

	ObjectKindLoadNode(TSharedPtr<FStreamableHandle> InWealthHandle, TArray<FObjectWealthEntry*>& InLoadedWealthEntry,
		TArray<FObjectWealthEntry*>& InUnloadWealthEntry, FName InObjectName, FName InFuncName)
	{
		WealthHandle = InWealthHandle;
		UnLoadWealthEntry = InUnloadWealthEntry;
		LoadedWealthEntry = InLoadedWealthEntry;
		ObjectName = InObjectName;
		FuncName = InFuncName;
	}
};

struct ClassSingleLoadNode
{
	//加载句柄
	TSharedPtr<FStreamableHandle> WealthHandle;
	//资源结构体
	FClassWealthEntry* WealthEntry;
	//目标对象
	FName ObjectName;
	//回调方法名
	FName FuncName;
	//生成位置
	FTransform SpawnTransform;
	//是否只加载UClass
	bool IsLoadClass;

	ClassSingleLoadNode(TSharedPtr<FStreamableHandle> InWealthHandle, FClassWealthEntry* InWealthEntry,
		FName InObjectName, FName InFuncName)
	{
		WealthHandle = InWealthHandle;
		WealthEntry = InWealthEntry;
		ObjectName = InObjectName;
		FuncName = InFuncName;
		IsLoadClass = true;
	}

	ClassSingleLoadNode(TSharedPtr<FStreamableHandle> InWealthHandle, FClassWealthEntry* InWealthEntry,
		FName InObjectName, FName InFuncName, FTransform InSpawnTransform)
	{
		WealthHandle = InWealthHandle;
		WealthEntry = InWealthEntry;
		ObjectName = InObjectName;
		FuncName = InFuncName;
		SpawnTransform = InSpawnTransform;
		IsLoadClass = false;
	}
};

struct ClassKindLoadNode
{
	//加载句柄
	TSharedPtr<FStreamableHandle> WealthHandle;
	//已经加载的资源
	TArray<FClassWealthEntry*> LoadedWealthEntry;
	//没有加载的资源
	TArray<FClassWealthEntry*> UnLoadWealthEntry;
	//目标对象
	FName ObjectName;
	//回调方法名
	FName FuncName;
	//生成位置
	TArray<FTransform> SpawnTransforms;
	//是否只加载UClass
	bool IsLoadClass;
	//保存生成的对象与名字
	TArray<FName> NameGroup;
	TArray<UObject*> ObjectGroup;
	TArray<AActor*> ActorGroup;
	TArray<UUserWidget*> WidgetGroup;

	ClassKindLoadNode(TSharedPtr<FStreamableHandle> InWealthHandle, TArray<FClassWealthEntry*>& InUnloadWealthEntry,
		TArray<FClassWealthEntry*>& InLoadedWealthEntry, FName InObjectName, FName InFuncName)
	{
		WealthHandle = InWealthHandle;
		UnLoadWealthEntry = InUnloadWealthEntry;
		LoadedWealthEntry = InLoadedWealthEntry;
		ObjectName = InObjectName;
		FuncName = InFuncName;
		IsLoadClass = true;
	}

	ClassKindLoadNode(TSharedPtr<FStreamableHandle> InWealthHandle, TArray<FClassWealthEntry*>& InUnloadWealthEntry,
		TArray<FClassWealthEntry*>& InLoadedWealthEntry, FName InObjectName, FName InFuncName, TArray<FTransform> InSpawnTransforms)
	{
		WealthHandle = InWealthHandle;
		UnLoadWealthEntry = InUnloadWealthEntry;
		LoadedWealthEntry = InLoadedWealthEntry;
		ObjectName = InObjectName;
		FuncName = InFuncName;
		SpawnTransforms = InSpawnTransforms;
		IsLoadClass = false;
	}
};

struct ClassMultiLoadNode
{
	//加载句柄
	TSharedPtr<FStreamableHandle> WealthHandle;
	//资源结构体
	FClassWealthEntry* WealthEntry;
	//请求对象名
	FName ObjectName;
	//回调方法名
	FName FuncName;
	//生成数量
	int32 Amount;
	//生成位置
	TArray<FTransform> SpawnTransforms;
	//保存生成的对象
	TArray<UObject*> ObjectGroup;
	TArray<AActor*> ActorGroup;
	TArray<UUserWidget*> WidgetGroup;
	//构造函数, 未加载时使用
	ClassMultiLoadNode(TSharedPtr<FStreamableHandle> InWealthHandle, FClassWealthEntry* InWealthEntry, int32 InAmount, FName InObjectName, FName InFuncName, TArray<FTransform> InSpawnTransforms)
	{
		WealthHandle = InWealthHandle;
		WealthEntry = InWealthEntry;
		Amount = InAmount;
		ObjectName = InObjectName;
		FuncName = InFuncName;
		SpawnTransforms = InSpawnTransforms;
	}
	//构造函数, 已加载时使用
	ClassMultiLoadNode(FClassWealthEntry* InWealthEntry, int32 InAmount, FName InObjectName, FName InFuncName, TArray<FTransform> InSpawnTransforms)
	{
		WealthEntry = InWealthEntry;
		Amount = InAmount;
		ObjectName = InObjectName;
		FuncName = InFuncName;
		SpawnTransforms = InSpawnTransforms;
	}
};

void UHFWealth::WealthBeginPlay()
{
	for (int i = 0; i < WealthData.Num(); ++i)
	{
		//生成Object对象
		for (int j = 0; j < WealthData[i]->AutoObjectData.Num(); ++j)
		{
			UObject* newObject = NewObject<UObject>(this, WealthData[i]->AutoObjectData[j].WealthClass);
			newObject->AddToRoot();
			IHFOOInterface* InstPtr = Cast<IHFOOInterface>(newObject);
			if (InstPtr)
			{
				InstPtr->RegisterToModule(WealthData[i]->ModuleName.IsNone() ? IModule->GetFName() : WealthData[i]->ModuleName,
					WealthData[i]->AutoObjectData[j].ObjectName,
					WealthData[i]->AutoObjectData[j].ClassName);
			}
		}
		//生成Actor对象
		for (int j = 0; j < WealthData[i]->AutoActorData.Num(); ++j)
		{
			AActor* NewAct = GetHFWorld()->SpawnActor<AActor>(WealthData[i]->AutoActorData[j].WealthClass, WealthData[i]->AutoActorData[j].Transform);
			IHFOOInterface* InstPtr = Cast<IHFOOInterface>(NewAct);
			if (InstPtr)
			{
				InstPtr->RegisterToModule(WealthData[i]->ModuleName.IsNone() ? IModule->GetFName() : WealthData[i]->ModuleName,
					WealthData[i]->AutoActorData[j].ObjectName,
					WealthData[i]->AutoActorData[j].ClassName);
			}
		}
		//生成Widget对象
		for (int j = 0; j < WealthData[i]->AutoWidgetData.Num(); ++j)
		{
			UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetHFWorld(), WealthData[i]->AutoWidgetData[j].WealthClass);
			GCWidgetGroup.Push(NewWidget);
			IHFOOInterface* InstPtr = Cast<IHFOOInterface>(NewWidget);
			if (InstPtr)
			{
				InstPtr->RegisterToModule(WealthData[i]->ModuleName.IsNone() ? IModule->GetFName() : WealthData[i]->ModuleName,
					WealthData[i]->AutoWidgetData[j].ObjectName,
					WealthData[i]->AutoWidgetData[j].ClassName);
			}
		}

#if WITH_EDITOR
		//循环设置WealthObject和WealthClass为空, 目的在于每次从编辑器启动游戏时资源Asset的状态都重置
		for (int j = 0; j < WealthData[i]->ObjectWealthData.Num(); ++j)
			WealthData[i]->ObjectWealthData[j].WealthObj = NULL;
		for (int j = 0; j < WealthData[i]->ClassWealthData.Num(); ++j)
			WealthData[i]->ClassWealthData[j].WealthClass = NULL;
#endif
	}


}

void UHFWealth::WealthTick(float DeltaSeconds)
{
	DealSingleObjLoadStack();
	DealKindObjectLoadStack();
	DealSingleClassLoadStack();
	DealKindClassLoadStack();
	DealMultiClassLoadStack();
}

void UHFWealth::AssignData(TArray<UWealthData*>& InWealthData)
{
	WealthData = InWealthData;
}

FWealthURL* UHFWealth::GainWealthURL(FName WealthName)
{
	for (int i = 0; i < WealthData.Num(); ++i)
	{
		for (int j = 0; j < WealthData[i]->WealthURL.Num(); ++j)
		{
			if (WealthData[i]->WealthURL[j].WealthName.IsEqual(WealthName))
			{
				return &WealthData[i]->WealthURL[j];
			}
		}
	}
	return nullptr;
}

void UHFWealth::GainWealthURL(FName WealthKind, TArray<FWealthURL*>& OutURL)
{
	for (int i = 0; i < WealthData.Num(); ++i)
	{
		for (int j = 0; j < WealthData[i]->WealthURL.Num(); ++j)
		{
			if (WealthData[i]->WealthURL[j].WealthKind.IsEqual(WealthKind))
			{
				OutURL.Push(&WealthData[i]->WealthURL[j]);
			}
		}
	}
}

void UHFWealth::LoadObjectWealth(FName WealthName, FName ObjectName, FName FuncName)
{
	FObjectWealthEntry* WealthEntry = GetSingleObjEntry(WealthName);
	if (!WealthEntry)
	{
		HFH::Debug() << ObjectName << " Get wealth is nullptr: " << WealthName << HFH::Endl();
		return;
	}
	if (!WealthEntry->WealthPath.IsValid())
	{
		HFH::Debug() << ObjectName << " Get wealth is invalid: " << WealthName << HFH::Endl();
		return;
	}
	//如果资源已经加载
	if (WealthEntry->WealthObj)
	{
		//直接返回给对象
		BackCallObjWealth(ModuleIndex, ObjectName, FuncName, WealthName, WealthEntry->WealthObj);
		//HFH::Debug() << "Loaded" << HFH::Endl();
	}
	else
	{
		//进行异步加载
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthEntry->WealthPath);
		ObjectSingleLoadStack.Push(new ObjectSingleLoadNode(WealthHandle, WealthEntry, ObjectName, FuncName));
		//HFH::Debug() << "Async Load..." << HFH::Endl();
	}
}

void UHFWealth::LoadObjectWealthKind(FName WealthKind, FName ObjectName, FName FuncName)
{
	TArray<FObjectWealthEntry*> WealthEntryGroup = GetKindObjEntry(WealthKind);
	if (!WealthEntryGroup.Num())
	{
		HFH::Debug() << ObjectName << " Get Null WealthKind: " << WealthKind << HFH::Endl();
		return;
	}
	for (int i = 0; i < WealthEntryGroup.Num(); ++i)
	{
		if (!WealthEntryGroup[i]->WealthPath.IsValid())
		{
			HFH::Debug() << ObjectName << " Get Invalid in Kind: " << WealthKind << " For Name: "
				<< WealthEntryGroup[i]->WealthName << HFH::Endl();
			return;
		}
	}
	//还没有加载的资源
	TArray<FObjectWealthEntry*> UnLoadWealthEntry;
	//已经加载的资源
	TArray<FObjectWealthEntry*> LoadedWealthEntry;
	for (int i = 0; i < WealthEntryGroup.Num(); ++i)
	{
		if (WealthEntryGroup[i]->WealthObj)
		{
			LoadedWealthEntry.Push(WealthEntryGroup[i]);
		}
		else
		{
			UnLoadWealthEntry.Push(WealthEntryGroup[i]);
		}
	}
	//如果资源已经都加载
	if (!UnLoadWealthEntry.Num())
	{
		TArray<FName> NameGroup;
		TArray<UObject*> WealthGroup;
		for (int i = 0; i < LoadedWealthEntry.Num(); ++i)
		{
			NameGroup.Push(LoadedWealthEntry[i]->WealthName);
			WealthGroup.Push(LoadedWealthEntry[i]->WealthObj);
		}
		BackCallObjWealthKind(ModuleIndex, ObjectName, FuncName, NameGroup, WealthGroup);
	}
	else
	{
		//获取资源路径
		TArray<FSoftObjectPath> WealthPaths;
		for (int i = 0; i < UnLoadWealthEntry.Num(); ++i)
		{
			WealthPaths.Push(UnLoadWealthEntry[i]->WealthPath);
		}
		//进行异步加载获取句柄
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthPaths);
		//生成加载节点
		ObjectKindLoadStack.Push(new ObjectKindLoadNode(WealthHandle, LoadedWealthEntry, UnLoadWealthEntry, ObjectName, FuncName));
	}
}

void UHFWealth::LoadUClassWealth(FName WealthName, FName ObjectName, FName FuncName)
{
	//获取资源结构体
	FClassWealthEntry* WealthEntry = GetSingleClassEntry(WealthName);
	if (!WealthEntry)
	{
		HFH::Debug() << ObjectName << " Get wealth is nullptr: " << WealthName << HFH::Endl();
		return;
	}
	if (!WealthEntry->WealthPtr.ToSoftObjectPath().IsValid())
	{
		HFH::Debug() << ObjectName << " Get wealth is invalid: " << WealthName << HFH::Endl();
		return;
	}
	//如果资源已经加载
	if (WealthEntry->WealthClass)
	{
		BackCallClassWealth(ModuleIndex, ObjectName, FuncName, WealthName, WealthEntry->WealthClass);
	}
	else
	{
		//进行异步加载
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthEntry->WealthPtr.ToSoftObjectPath());
		ClassSingleLoadStack.Push(new ClassSingleLoadNode(WealthHandle, WealthEntry, ObjectName, FuncName));
	}
}

void UHFWealth::LoadUClassWealthKind(FName WealthKind, FName ObjectName, FName FuncName)
{
	TArray<FClassWealthEntry*> WealthEntryGroup = GetKindClassEntry(WealthKind);
	//如果数量为0
	if (WealthEntryGroup.Num() == 0)
	{
		HFH::Debug() << ObjectName << " Get Null WealthKind : " << WealthKind << HFH::Endl();
		return;
	}
	//判断资源可用性
	for (int i = 0; i < WealthEntryGroup.Num(); ++i)
	{
		if (!WealthEntryGroup[i]->WealthPtr.ToSoftObjectPath().IsValid())
		{
			HFH::Debug() << ObjectName << " Get Not Valid in Kind : " << WealthKind << " For Name : " << WealthEntryGroup[i]->WealthName << HFH::Endl();
			return;
		}
	}
	//未加载资源序列
	TArray<FClassWealthEntry*> UnLoadWealthEntry;
	//已加载资源序列
	TArray<FClassWealthEntry*> LoadWealthEntry;
	//分类保存
	for (int i = 0; i < WealthEntryGroup.Num(); ++i)
	{
		if (WealthEntryGroup[i]->WealthClass)
			LoadWealthEntry.Push(WealthEntryGroup[i]);
		else
			UnLoadWealthEntry.Push(WealthEntryGroup[i]);
	}
	//判断所有资源是否都已经加载
	if (UnLoadWealthEntry.Num() == 0)
	{
		//填充参数
		TArray<FName> NameGroup;
		TArray<UClass*> WealthGroup;
		for (int i = 0; i < LoadWealthEntry.Num(); ++i)
		{
			NameGroup.Push(LoadWealthEntry[i]->WealthName);
			WealthGroup.Push(LoadWealthEntry[i]->WealthClass);
		}
		//返回资源给请求对象
		BackCallClassWealthKind(ModuleIndex, ObjectName, FuncName, NameGroup, WealthGroup);
	}
	else
	{
		//获取未加载资源路径数组
		TArray<FSoftObjectPath> WealthPaths;
		for (int i = 0; i < UnLoadWealthEntry.Num(); ++i)
			WealthPaths.Push(UnLoadWealthEntry[i]->WealthPtr.ToSoftObjectPath());
		//进行异步加载获取句柄
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthPaths);
		//添加新的加载节点
		ClassKindLoadStack.Push(new ClassKindLoadNode(WealthHandle, UnLoadWealthEntry, LoadWealthEntry, ObjectName, FuncName));
	}
}

void UHFWealth::BuildSingleClassWealth(EWealthType WealthType, FName WealthName, FName ObjectName, FName FuncName, FTransform SpawnTransform)
{
	//获取对应的资源结构体
	FClassWealthEntry* WealthEntry = GetSingleClassEntry(WealthName);
	//如果为空
	if (!WealthEntry)
	{
		HFH::Debug() << ObjectName << " Get Null Wealth : " << WealthName << HFH::Endl();
		return;
	}
	//如果资源不可用
	if (!WealthEntry->WealthPtr.ToSoftObjectPath().IsValid())
	{
		HFH::Debug() << ObjectName << " Get UnValid Wealth : " << WealthName << HFH::Endl();
		return;
	}
	//资源类型是否匹配
	if (WealthEntry->WealthType != WealthType)
	{
		HFH::Debug() << ObjectName << " Get Error Type : " << WealthName << HFH::Endl();
	}
	//如果资源已经加载
	if (WealthEntry->WealthClass)
	{
		//生成并且传递对象到请求者
		if (WealthType == EWealthType::Object)
		{
			UObject* InstObject = NewObject<UObject>(this, WealthEntry->WealthClass);
			InstObject->AddToRoot();
			BackCallObjectSingle(ModuleIndex, ObjectName, FuncName, WealthName, InstObject);
		}
		else if (WealthType == EWealthType::Actor)
		{
			AActor* InstActor = GetHFWorld()->SpawnActor<AActor>(WealthEntry->WealthClass, SpawnTransform);
			BackCallActorSingle(ModuleIndex, ObjectName, FuncName, WealthName, InstActor);
		}
		else if (WealthType == EWealthType::Widget)
		{
			UUserWidget* InstWidget = CreateWidget<UUserWidget>(GetHFWorld(), WealthEntry->WealthClass);
			//避免回收
			GCWidgetGroup.Push(InstWidget);
			BackCallWidgetSingle(ModuleIndex, ObjectName, FuncName, WealthName, InstWidget);
		}
	}
	else
	{
		//异步加载, 获取加载句柄
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthEntry->WealthPtr.ToSoftObjectPath());
		//创建新加载节点
		ClassSingleLoadStack.Push(new ClassSingleLoadNode(WealthHandle, WealthEntry, ObjectName, FuncName, SpawnTransform));
	}
}

void UHFWealth::BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName ObjectName, FName FuncName, TArray<FTransform> SpawnTransforms)
{
	TArray<FClassWealthEntry*> WealthEntrytGroup = GetKindClassEntry(WealthKind);
	//判断为0
	if (WealthEntrytGroup.Num() == 0)
	{
		HFH::Debug() << ObjectName << " Get Null WealthKind : " << WealthKind << HFH::Endl();
		return;
	}
	for (int i = 0; i < WealthEntrytGroup.Num(); ++i)
	{
		//资源可用性
		if (!WealthEntrytGroup[i]->WealthPtr.ToSoftObjectPath().IsValid())
		{
			HFH::Debug() << ObjectName << " Get Not Vaild In Kind : " << WealthKind << " For Name : " << WealthEntrytGroup[i]->WealthName << HFH::Endl();
			return;
		}
		//资源类型匹配
		if (WealthEntrytGroup[i]->WealthType != WealthType)
		{
			HFH::Debug() << ObjectName << " Get Error Type In Kind : " << WealthKind << " For Name : " << WealthEntrytGroup[i]->WealthName << HFH::Endl();
			return;
		}
	}
	//判断Transform数组是否为1或者是否为WealthEntrytGroup的数量
	if (WealthType == EWealthType::Actor && SpawnTransforms.Num() != 1 && SpawnTransforms.Num() != WealthEntrytGroup.Num())
	{
		HFH::Debug() << ObjectName << " Send Error Spawn Count : " << WealthKind << HFH::Endl();
		return;
	}
	//未加载的资源链接
	TArray<FClassWealthEntry*> UnLoadWealthEntry;
	//已加载资源链接
	TArray<FClassWealthEntry*> LoadWealthEntry;
	//资源分类
	for (int i = 0; i < WealthEntrytGroup.Num(); ++i)
	{
		if (WealthEntrytGroup[i]->WealthClass)
			LoadWealthEntry.Push(WealthEntrytGroup[i]);
		else
			UnLoadWealthEntry.Push(WealthEntrytGroup[i]);
	}
	//声明一个加载句柄
	TSharedPtr<FStreamableHandle> WealthHandle;
	//如果有未加载的资源
	if (UnLoadWealthEntry.Num() > 0)
	{
		//获取资源路径
		TArray<FSoftObjectPath> WealthPaths;
		for (int i = 0; i < UnLoadWealthEntry.Num(); ++i)
			WealthPaths.Push(UnLoadWealthEntry[i]->WealthPtr.ToSoftObjectPath());
		//获取加载句柄
		WealthHandle = WealthLoader.RequestAsyncLoad(WealthPaths);
	}
	//创建帧处理的节点
	ClassKindLoadStack.Push(new ClassKindLoadNode(WealthHandle, UnLoadWealthEntry, LoadWealthEntry, ObjectName, FuncName, SpawnTransforms));
}

void UHFWealth::BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName ObjectName, FName FuncName, TArray<FTransform> SpawnTransforms)
{
	//获取对应的资源结构体
	FClassWealthEntry* WealthEntry = GetSingleClassEntry(WealthName);
	//如果为空
	if (!WealthEntry)
	{
		HFH::Debug() << ObjectName << " Get Null Wealth : " << WealthName << HFH::Endl();
		return;
	}
	//如果资源不可用
	if (!WealthEntry->WealthPtr.ToSoftObjectPath().IsValid())
	{
		HFH::Debug() << ObjectName << " Get UnValid Wealth : " << WealthName << HFH::Endl();
		return;
	}
	//资源类型是否匹配
	if (WealthEntry->WealthType != WealthType)
	{
		HFH::Debug() << ObjectName << " Get Error Type : " << WealthName << HFH::Endl();
		return;
	}
	//验证Transform数组的数量是否为1或者Amount = 0
	if ((WealthType == EWealthType::Actor && SpawnTransforms.Num() != 1 && SpawnTransforms.Num() != Amount) || Amount == 0)
	{
		HFH::Debug() << ObjectName << " Send Error Spawn Count : " << WealthName << HFH::Endl();
		return;
	}
	//如果已经加载资源
	if (WealthEntry->WealthClass)
		ClassMultiLoadStack.Push(new ClassMultiLoadNode(WealthEntry, Amount, ObjectName, FuncName, SpawnTransforms));
	else
	{
		//异步加载
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthEntry->WealthPtr.ToSoftObjectPath());
		//添加新节点
		ClassMultiLoadStack.Push(new ClassMultiLoadNode(WealthHandle, WealthEntry, Amount, ObjectName, FuncName, SpawnTransforms));
	}
}

FObjectWealthEntry* UHFWealth::GetSingleObjEntry(FName WealthName)
{
	for (int i = 0; i < WealthData.Num(); ++i)
	{
		for (int j = 0; j < WealthData[i]->ObjectWealthData.Num(); ++j)
		{
			if (WealthData[i]->ObjectWealthData[j].WealthName.IsEqual(WealthName))
			{
				return &(WealthData[i]->ObjectWealthData[j]);
			}
		}
	}
	return nullptr;
}

TArray<FObjectWealthEntry*> UHFWealth::GetKindObjEntry(FName WealthKind)
{
	TArray<FObjectWealthEntry*> WealthGroup;
	for (int i = 0; i < WealthData.Num(); ++i)
	{
		for (int j = 0; j < WealthData[i]->ObjectWealthData.Num(); ++j)
		{
			if (WealthData[i]->ObjectWealthData[j].WealthKind.IsEqual(WealthKind))
			{
				WealthGroup.Push(&(WealthData[i]->ObjectWealthData[j]));
			}
		}
	}
	return WealthGroup;
}

FClassWealthEntry* UHFWealth::GetSingleClassEntry(FName WealthName)
{
	for (int i = 0; i < WealthData.Num(); ++i)
	{
		for (int j = 0; j < WealthData[i]->ClassWealthData.Num(); ++j)
		{
			if (WealthData[i]->ClassWealthData[j].WealthName.IsEqual(WealthName))
			{
				return &(WealthData[i]->ClassWealthData[j]);
			}
		}
	}
	return nullptr;
}

TArray<FClassWealthEntry*> UHFWealth::GetKindClassEntry(FName WealthKind)
{
	TArray<FClassWealthEntry*> WealthGroup;
	for (int i = 0; i < WealthData.Num(); ++i)
	{
		for (int j = 0; j < WealthData[i]->ClassWealthData.Num(); ++j)
		{
			if (WealthData[i]->ClassWealthData[j].WealthKind.IsEqual(WealthKind))
			{
				WealthGroup.Push(&(WealthData[i]->ClassWealthData[j]));
			}
		}
	}
	return WealthGroup;
}

void UHFWealth::DealSingleObjLoadStack()
{
	//定义加载完成的序列
	TArray<ObjectSingleLoadNode*> CompleteStack;
	for (int i = 0; i < ObjectSingleLoadStack.Num(); ++i)
	{
		//判断是否已经加载完成
		if (ObjectSingleLoadStack[i]->WealthHandle->HasLoadCompleted())
		{
			//设置对应资源完成
			ObjectSingleLoadStack[i]->WealthEntry->WealthObj = ObjectSingleLoadStack[i]->WealthEntry->WealthPath.ResolveObject();
			//返回资源给对象
			BackCallObjWealth(ModuleIndex, ObjectSingleLoadStack[i]->ObjectName, ObjectSingleLoadStack[i]->FuncName,
				ObjectSingleLoadStack[i]->WealthEntry->WealthName, ObjectSingleLoadStack[i]->WealthEntry->WealthObj);
			//添加已经加载完成的节点到临时序列
			CompleteStack.Push(ObjectSingleLoadStack[i]);
		}
	}
	//销毁已经完成的节点
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ObjectSingleLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}

void UHFWealth::DealKindObjectLoadStack()
{
	//定义加载完成的序列
	TArray<ObjectKindLoadNode*> CompleteStack;
	for (int i = 0; i < ObjectKindLoadStack.Num(); ++i)
	{
		if (ObjectKindLoadStack[i]->WealthHandle->HasLoadCompleted())
		{			
			TArray<FName> NameGroup;
			TArray<UObject*> WealthGroup;
			for (int j = 0; j < ObjectKindLoadStack[i]->LoadedWealthEntry.Num(); ++j)
			{
				NameGroup.Push(ObjectKindLoadStack[i]->LoadedWealthEntry[j]->WealthName);
				WealthGroup.Push(ObjectKindLoadStack[i]->LoadedWealthEntry[j]->WealthObj);
			}
			for (int j = 0; j < ObjectKindLoadStack[i]->UnLoadWealthEntry.Num(); ++j)
			{
				ObjectKindLoadStack[i]->UnLoadWealthEntry[j]->WealthObj = ObjectKindLoadStack[i]->UnLoadWealthEntry[j]->WealthPath.ResolveObject();
				NameGroup.Push(ObjectKindLoadStack[i]->UnLoadWealthEntry[j]->WealthName);
				WealthGroup.Push(ObjectKindLoadStack[i]->UnLoadWealthEntry[j]->WealthObj);
			}
			BackCallObjWealthKind(ModuleIndex, ObjectKindLoadStack[i]->ObjectName, ObjectKindLoadStack[i]->FuncName, NameGroup, WealthGroup);
			CompleteStack.Push(ObjectKindLoadStack[i]);
		}
	}

	//销毁已经完成的节点
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ObjectKindLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}

void UHFWealth::DealSingleClassLoadStack()
{
	//定义加载完成的序列
	TArray<ClassSingleLoadNode*> CompleteStack;
	for (int i = 0; i < ClassSingleLoadStack.Num(); ++i)
	{
		//判断是否已经加载完成
		if (ClassSingleLoadStack[i]->WealthHandle->HasLoadCompleted())
		{
			//设置对应资源完成
			ClassSingleLoadStack[i]->WealthEntry->WealthClass = Cast<UClass>(ClassSingleLoadStack[i]->WealthEntry->WealthPtr.ToSoftObjectPath().ResolveObject());
			//判断是否生成对象
			if (ClassSingleLoadStack[i]->IsLoadClass)
			{
				//返回资源给对象
				BackCallClassWealth(ModuleIndex, ClassSingleLoadStack[i]->ObjectName, ClassSingleLoadStack[i]->FuncName,
					ClassSingleLoadStack[i]->WealthEntry->WealthName, ClassSingleLoadStack[i]->WealthEntry->WealthClass);
			}
			else
			{
				//生成并且传递对象到请求者
				if (ClassSingleLoadStack[i]->WealthEntry->WealthType == EWealthType::Object)
				{
					UObject* InstObj = NewObject<UObject>(this, ClassSingleLoadStack[i]->WealthEntry->WealthClass);
					InstObj->AddToRoot();
					BackCallObjectSingle(ModuleIndex, ClassSingleLoadStack[i]->ObjectName, ClassSingleLoadStack[i]->FuncName,
						ClassSingleLoadStack[i]->WealthEntry->WealthName, InstObj);
				}
				else if (ClassSingleLoadStack[i]->WealthEntry->WealthType == EWealthType::Actor)
				{
					AActor* InstActor = GetHFWorld()->SpawnActor<AActor>(ClassSingleLoadStack[i]->WealthEntry->WealthClass, ClassSingleLoadStack[i]->SpawnTransform);
					BackCallActorSingle(ModuleIndex, ClassSingleLoadStack[i]->ObjectName, ClassSingleLoadStack[i]->FuncName,
						ClassSingleLoadStack[i]->WealthEntry->WealthName, InstActor);
				}
				else if (ClassSingleLoadStack[i]->WealthEntry->WealthType == EWealthType::Widget)
				{
					UUserWidget* InstWidget = CreateWidget<UUserWidget>(GetHFWorld(), ClassSingleLoadStack[i]->WealthEntry->WealthClass);
					//避免回收
					GCWidgetGroup.Push(InstWidget);
					BackCallWidgetSingle(ModuleIndex, ClassSingleLoadStack[i]->ObjectName, ClassSingleLoadStack[i]->FuncName,
						ClassSingleLoadStack[i]->WealthEntry->WealthName, InstWidget);
				}
			}
			
			//添加已经加载完成的节点到临时序列
			CompleteStack.Push(ClassSingleLoadStack[i]);
		}
	}
	//销毁已经完成的节点
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ClassSingleLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}

void UHFWealth::DealKindClassLoadStack()
{
	//定义已完成加载节点序列
	TArray<ClassKindLoadNode*> CompleteStack;
	for (int i = 0; i < ClassKindLoadStack.Num(); ++i)
	{
		//判断第一次加载完成, WealthHandle已经加载完成, UnLoadWealthEntry数量大于0
		if (ClassKindLoadStack[i]->WealthHandle.IsValid() && ClassKindLoadStack[i]->WealthHandle->HasLoadCompleted() && ClassKindLoadStack[i]->UnLoadWealthEntry.Num() > 0)
		{
			//如果已经加载完成, 设置未加载序列的资源指针
			for (int j = 0; j < ClassKindLoadStack[i]->UnLoadWealthEntry.Num(); ++j)
				ClassKindLoadStack[i]->UnLoadWealthEntry[j]->WealthClass = Cast<UClass>(ClassKindLoadStack[i]->UnLoadWealthEntry[j]->WealthPtr.ToSoftObjectPath().ResolveObject());
			//将未加载完成序列里的资源填充到已加载资源序列
			ClassKindLoadStack[i]->LoadedWealthEntry.Append(ClassKindLoadStack[i]->UnLoadWealthEntry);
			//清空UnLoadWealthEntry
			ClassKindLoadStack[i]->UnLoadWealthEntry.Empty();
		}

		//如果未加载序列为0, 说明已经加载完成
		if (ClassKindLoadStack[i]->UnLoadWealthEntry.Num() == 0)
		{
			//加载UClass或者直接生成资源的情况来处理
			if (ClassKindLoadStack[i]->IsLoadClass)
			{
				//设置反射参数
				TArray<FName> NameGroup;
				TArray<UClass*> WealthGroup;
				for (int j = 0; j < ClassKindLoadStack[i]->LoadedWealthEntry.Num(); ++j)
				{
					NameGroup.Push(ClassKindLoadStack[i]->LoadedWealthEntry[j]->WealthName);
					WealthGroup.Push(ClassKindLoadStack[i]->LoadedWealthEntry[j]->WealthClass);
				}
				//返回资源给请求对象
				BackCallClassWealthKind(ModuleIndex, ClassKindLoadStack[i]->ObjectName, ClassKindLoadStack[i]->FuncName, NameGroup, WealthGroup);
				//添加该节点到已完成序列
				CompleteStack.Push(ClassKindLoadStack[i]);
			}
			else //如果要生成对象
			{
				//从已加载的资源数组中取出第一个
				FClassWealthEntry* WealthEntry = ClassKindLoadStack[i]->LoadedWealthEntry[0];
				//移除出序列
				ClassKindLoadStack[i]->LoadedWealthEntry.RemoveAt(0);
				//根据资源类型生成对象
				if (WealthEntry->WealthType == EWealthType::Object)
				{
					UObject* InstObject = NewObject<UObject>(this, WealthEntry->WealthClass);
					InstObject->AddToRoot();
					//添加找参数数组
					ClassKindLoadStack[i]->NameGroup.Push(WealthEntry->WealthName);
					ClassKindLoadStack[i]->ObjectGroup.Push(InstObject);
					//判断是否生成了全部的对象
					if (ClassKindLoadStack[i]->LoadedWealthEntry.Num() == 0)
					{
						//给请求者传递生成的对象
						BackCallObjectKind(ModuleIndex, ClassKindLoadStack[i]->ObjectName, ClassKindLoadStack[i]->FuncName, ClassKindLoadStack[i]->NameGroup, ClassKindLoadStack[i]->ObjectGroup);
						//添加到完成序列
						CompleteStack.Push(ClassKindLoadStack[i]);
					}
				}
				else if (WealthEntry->WealthType == EWealthType::Actor)
				{
					//获取生成位置
					FTransform SpawnTransform = ClassKindLoadStack[i]->SpawnTransforms.Num() == 1 ? ClassKindLoadStack[i]->SpawnTransforms[0] : ClassKindLoadStack[i]->SpawnTransforms[ClassKindLoadStack[i]->ActorGroup.Num()];
					//生成对象
					AActor* InstActor = GetHFWorld()->SpawnActor<AActor>(WealthEntry->WealthClass, SpawnTransform);
					//添加到参数数组
					ClassKindLoadStack[i]->NameGroup.Push(WealthEntry->WealthName);
					ClassKindLoadStack[i]->ActorGroup.Push(InstActor);
					//判断是否生成了全部的对象
					if (ClassKindLoadStack[i]->LoadedWealthEntry.Num() == 0)
					{
						//给请求者传递生成的对象
						BackCallActorKind(ModuleIndex, ClassKindLoadStack[i]->ObjectName, ClassKindLoadStack[i]->FuncName, ClassKindLoadStack[i]->NameGroup, ClassKindLoadStack[i]->ActorGroup);
						//添加到完成序列
						CompleteStack.Push(ClassKindLoadStack[i]);
					}
				}
				else if (WealthEntry->WealthType == EWealthType::Widget)
				{
					UUserWidget* InstWidget = CreateWidget<UUserWidget>(GetHFWorld(), WealthEntry->WealthClass);
					//避免回收
					GCWidgetGroup.Push(InstWidget);
					//添加到参数数组
					ClassKindLoadStack[i]->NameGroup.Push(WealthEntry->WealthName);
					ClassKindLoadStack[i]->WidgetGroup.Push(InstWidget);
					//判断是否生成了全部的对象
					if (ClassKindLoadStack[i]->LoadedWealthEntry.Num() == 0)
					{
						//给请求者传递生成的对象
						BackCallWidgetKind(ModuleIndex, ClassKindLoadStack[i]->ObjectName, ClassKindLoadStack[i]->FuncName, ClassKindLoadStack[i]->NameGroup, ClassKindLoadStack[i]->WidgetGroup);
						//添加到完成序列
						CompleteStack.Push(ClassKindLoadStack[i]);
					}
				}
			}
		}
	}
	//清空已完成节点
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ClassKindLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}

void UHFWealth::DealMultiClassLoadStack()
{
	//定义完成的节点
	TArray<ClassMultiLoadNode*> CompleteStack;
	for (int i = 0; i < ClassMultiLoadStack.Num(); ++i)
	{
		//如果没有加载UClass, 说明加载句柄有效
		if (!ClassMultiLoadStack[i]->WealthEntry->WealthClass)
		{
			//如果加载句柄加载完毕
			if (ClassMultiLoadStack[i]->WealthHandle->HasLoadCompleted())
				ClassMultiLoadStack[i]->WealthEntry->WealthClass = Cast<UClass>(ClassMultiLoadStack[i]->WealthHandle->GetLoadedAsset());
		}
		//再次判断WealthClass是否存在, 如果存在进入生成对象阶段
		if (ClassMultiLoadStack[i]->WealthEntry->WealthClass)
		{
			//区分类型生成对
			if (ClassMultiLoadStack[i]->WealthEntry->WealthType == EWealthType::Object)
			{
				UObject* InstObject = NewObject<UObject>(this, ClassMultiLoadStack[i]->WealthEntry->WealthClass);
				InstObject->AddToRoot();
				ClassMultiLoadStack[i]->ObjectGroup.Push(InstObject);
				//如果生产完毕
				if (ClassMultiLoadStack[i]->ObjectGroup.Num() == ClassMultiLoadStack[i]->Amount)
				{
					//返回对象给请求者
					BackCallObjectMulti(ModuleIndex, ClassMultiLoadStack[i]->ObjectName, ClassMultiLoadStack[i]->FuncName, ClassMultiLoadStack[i]->WealthEntry->WealthName, ClassMultiLoadStack[i]->ObjectGroup);
					//添加到完成序列
					CompleteStack.Push(ClassMultiLoadStack[i]);
				}
			}
			else if (ClassMultiLoadStack[i]->WealthEntry->WealthType == EWealthType::Actor)
			{
				//获取生成位置
				FTransform SpawnTransform = ClassMultiLoadStack[i]->SpawnTransforms.Num() == 1 ? ClassMultiLoadStack[i]->SpawnTransforms[0] : ClassMultiLoadStack[i]->SpawnTransforms[ClassMultiLoadStack[i]->ActorGroup.Num()];
				//生成对象
				AActor* InstActor = GetHFWorld()->SpawnActor<AActor>(ClassMultiLoadStack[i]->WealthEntry->WealthClass, SpawnTransform);
				//添加参数数组
				ClassMultiLoadStack[i]->ActorGroup.Push(InstActor);
				//判断是否生成了全部的对象
				if (ClassMultiLoadStack[i]->ActorGroup.Num() == ClassMultiLoadStack[i]->Amount)
				{
					//给请求者传递生成的对象
					BackCallActorMulti(ModuleIndex, ClassMultiLoadStack[i]->ObjectName, ClassMultiLoadStack[i]->FuncName, ClassMultiLoadStack[i]->WealthEntry->WealthName, ClassMultiLoadStack[i]->ActorGroup);
					//添加到完成序列
					CompleteStack.Push(ClassMultiLoadStack[i]);
				}
			}
			else if (ClassMultiLoadStack[i]->WealthEntry->WealthType == EWealthType::Widget)
			{
				UUserWidget* InstWidget = CreateWidget<UUserWidget>(GetHFWorld(), ClassMultiLoadStack[i]->WealthEntry->WealthClass);
				//避免回收
				GCWidgetGroup.Push(InstWidget);
				//添加参数数组
				ClassMultiLoadStack[i]->WidgetGroup.Push(InstWidget);
				//判断是否生成了全部的对象
				if (ClassMultiLoadStack[i]->WidgetGroup.Num() == ClassMultiLoadStack[i]->Amount)
				{
					//给请求者传递生成的对象
					BackCallWidgetMulti(ModuleIndex, ClassMultiLoadStack[i]->ObjectName, ClassMultiLoadStack[i]->FuncName, ClassMultiLoadStack[i]->WealthEntry->WealthName, ClassMultiLoadStack[i]->WidgetGroup);
					//添加到完成序列
					CompleteStack.Push(ClassMultiLoadStack[i]);
				}
			}
		}
	}
	//清空已完成节点
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ClassMultiLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}
