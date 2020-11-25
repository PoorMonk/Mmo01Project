// Fill out your copyright notice in the Description page of Project Settings.


#include "HFCore/HFWealth.h"
#include "HFObject/HFOOInterface.h"
#include "Blueprint/UserWidget.h"

struct ObjectSingleLoadNode
{
	//���ؾ��
	TSharedPtr<FStreamableHandle> WealthHandle;
	//��Դ�ṹ��
	FObjectWealthEntry* WealthEntry;
	//Ŀ�����
	FName ObjectName;
	//�ص�������
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
	//���ؾ��
	TSharedPtr<FStreamableHandle> WealthHandle;
	//�Ѿ����ص���Դ
	TArray<FObjectWealthEntry*> LoadedWealthEntry;
	//û�м��ص���Դ
	TArray<FObjectWealthEntry*> UnLoadWealthEntry;
	//Ŀ�����
	FName ObjectName;
	//�ص�������
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
	//���ؾ��
	TSharedPtr<FStreamableHandle> WealthHandle;
	//��Դ�ṹ��
	FClassWealthEntry* WealthEntry;
	//Ŀ�����
	FName ObjectName;
	//�ص�������
	FName FuncName;
	//����λ��
	FTransform SpawnTransform;
	//�Ƿ�ֻ����UClass
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
	//���ؾ��
	TSharedPtr<FStreamableHandle> WealthHandle;
	//�Ѿ����ص���Դ
	TArray<FClassWealthEntry*> LoadedWealthEntry;
	//û�м��ص���Դ
	TArray<FClassWealthEntry*> UnLoadWealthEntry;
	//Ŀ�����
	FName ObjectName;
	//�ص�������
	FName FuncName;
	//����λ��
	TArray<FTransform> SpawnTransforms;
	//�Ƿ�ֻ����UClass
	bool IsLoadClass;
	//�������ɵĶ���������
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
	//���ؾ��
	TSharedPtr<FStreamableHandle> WealthHandle;
	//��Դ�ṹ��
	FClassWealthEntry* WealthEntry;
	//���������
	FName ObjectName;
	//�ص�������
	FName FuncName;
	//��������
	int32 Amount;
	//����λ��
	TArray<FTransform> SpawnTransforms;
	//�������ɵĶ���
	TArray<UObject*> ObjectGroup;
	TArray<AActor*> ActorGroup;
	TArray<UUserWidget*> WidgetGroup;
	//���캯��, δ����ʱʹ��
	ClassMultiLoadNode(TSharedPtr<FStreamableHandle> InWealthHandle, FClassWealthEntry* InWealthEntry, int32 InAmount, FName InObjectName, FName InFuncName, TArray<FTransform> InSpawnTransforms)
	{
		WealthHandle = InWealthHandle;
		WealthEntry = InWealthEntry;
		Amount = InAmount;
		ObjectName = InObjectName;
		FuncName = InFuncName;
		SpawnTransforms = InSpawnTransforms;
	}
	//���캯��, �Ѽ���ʱʹ��
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
		//����Object����
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
		//����Actor����
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
		//����Widget����
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
		//ѭ������WealthObject��WealthClassΪ��, Ŀ������ÿ�δӱ༭��������Ϸʱ��ԴAsset��״̬������
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
	//�����Դ�Ѿ�����
	if (WealthEntry->WealthObj)
	{
		//ֱ�ӷ��ظ�����
		BackCallObjWealth(ModuleIndex, ObjectName, FuncName, WealthName, WealthEntry->WealthObj);
		//HFH::Debug() << "Loaded" << HFH::Endl();
	}
	else
	{
		//�����첽����
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
	//��û�м��ص���Դ
	TArray<FObjectWealthEntry*> UnLoadWealthEntry;
	//�Ѿ����ص���Դ
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
	//�����Դ�Ѿ�������
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
		//��ȡ��Դ·��
		TArray<FSoftObjectPath> WealthPaths;
		for (int i = 0; i < UnLoadWealthEntry.Num(); ++i)
		{
			WealthPaths.Push(UnLoadWealthEntry[i]->WealthPath);
		}
		//�����첽���ػ�ȡ���
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthPaths);
		//���ɼ��ؽڵ�
		ObjectKindLoadStack.Push(new ObjectKindLoadNode(WealthHandle, LoadedWealthEntry, UnLoadWealthEntry, ObjectName, FuncName));
	}
}

void UHFWealth::LoadUClassWealth(FName WealthName, FName ObjectName, FName FuncName)
{
	//��ȡ��Դ�ṹ��
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
	//�����Դ�Ѿ�����
	if (WealthEntry->WealthClass)
	{
		BackCallClassWealth(ModuleIndex, ObjectName, FuncName, WealthName, WealthEntry->WealthClass);
	}
	else
	{
		//�����첽����
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthEntry->WealthPtr.ToSoftObjectPath());
		ClassSingleLoadStack.Push(new ClassSingleLoadNode(WealthHandle, WealthEntry, ObjectName, FuncName));
	}
}

void UHFWealth::LoadUClassWealthKind(FName WealthKind, FName ObjectName, FName FuncName)
{
	TArray<FClassWealthEntry*> WealthEntryGroup = GetKindClassEntry(WealthKind);
	//�������Ϊ0
	if (WealthEntryGroup.Num() == 0)
	{
		HFH::Debug() << ObjectName << " Get Null WealthKind : " << WealthKind << HFH::Endl();
		return;
	}
	//�ж���Դ������
	for (int i = 0; i < WealthEntryGroup.Num(); ++i)
	{
		if (!WealthEntryGroup[i]->WealthPtr.ToSoftObjectPath().IsValid())
		{
			HFH::Debug() << ObjectName << " Get Not Valid in Kind : " << WealthKind << " For Name : " << WealthEntryGroup[i]->WealthName << HFH::Endl();
			return;
		}
	}
	//δ������Դ����
	TArray<FClassWealthEntry*> UnLoadWealthEntry;
	//�Ѽ�����Դ����
	TArray<FClassWealthEntry*> LoadWealthEntry;
	//���ౣ��
	for (int i = 0; i < WealthEntryGroup.Num(); ++i)
	{
		if (WealthEntryGroup[i]->WealthClass)
			LoadWealthEntry.Push(WealthEntryGroup[i]);
		else
			UnLoadWealthEntry.Push(WealthEntryGroup[i]);
	}
	//�ж�������Դ�Ƿ��Ѿ�����
	if (UnLoadWealthEntry.Num() == 0)
	{
		//������
		TArray<FName> NameGroup;
		TArray<UClass*> WealthGroup;
		for (int i = 0; i < LoadWealthEntry.Num(); ++i)
		{
			NameGroup.Push(LoadWealthEntry[i]->WealthName);
			WealthGroup.Push(LoadWealthEntry[i]->WealthClass);
		}
		//������Դ���������
		BackCallClassWealthKind(ModuleIndex, ObjectName, FuncName, NameGroup, WealthGroup);
	}
	else
	{
		//��ȡδ������Դ·������
		TArray<FSoftObjectPath> WealthPaths;
		for (int i = 0; i < UnLoadWealthEntry.Num(); ++i)
			WealthPaths.Push(UnLoadWealthEntry[i]->WealthPtr.ToSoftObjectPath());
		//�����첽���ػ�ȡ���
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthPaths);
		//����µļ��ؽڵ�
		ClassKindLoadStack.Push(new ClassKindLoadNode(WealthHandle, UnLoadWealthEntry, LoadWealthEntry, ObjectName, FuncName));
	}
}

void UHFWealth::BuildSingleClassWealth(EWealthType WealthType, FName WealthName, FName ObjectName, FName FuncName, FTransform SpawnTransform)
{
	//��ȡ��Ӧ����Դ�ṹ��
	FClassWealthEntry* WealthEntry = GetSingleClassEntry(WealthName);
	//���Ϊ��
	if (!WealthEntry)
	{
		HFH::Debug() << ObjectName << " Get Null Wealth : " << WealthName << HFH::Endl();
		return;
	}
	//�����Դ������
	if (!WealthEntry->WealthPtr.ToSoftObjectPath().IsValid())
	{
		HFH::Debug() << ObjectName << " Get UnValid Wealth : " << WealthName << HFH::Endl();
		return;
	}
	//��Դ�����Ƿ�ƥ��
	if (WealthEntry->WealthType != WealthType)
	{
		HFH::Debug() << ObjectName << " Get Error Type : " << WealthName << HFH::Endl();
	}
	//�����Դ�Ѿ�����
	if (WealthEntry->WealthClass)
	{
		//���ɲ��Ҵ��ݶ���������
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
			//�������
			GCWidgetGroup.Push(InstWidget);
			BackCallWidgetSingle(ModuleIndex, ObjectName, FuncName, WealthName, InstWidget);
		}
	}
	else
	{
		//�첽����, ��ȡ���ؾ��
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthEntry->WealthPtr.ToSoftObjectPath());
		//�����¼��ؽڵ�
		ClassSingleLoadStack.Push(new ClassSingleLoadNode(WealthHandle, WealthEntry, ObjectName, FuncName, SpawnTransform));
	}
}

void UHFWealth::BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName ObjectName, FName FuncName, TArray<FTransform> SpawnTransforms)
{
	TArray<FClassWealthEntry*> WealthEntrytGroup = GetKindClassEntry(WealthKind);
	//�ж�Ϊ0
	if (WealthEntrytGroup.Num() == 0)
	{
		HFH::Debug() << ObjectName << " Get Null WealthKind : " << WealthKind << HFH::Endl();
		return;
	}
	for (int i = 0; i < WealthEntrytGroup.Num(); ++i)
	{
		//��Դ������
		if (!WealthEntrytGroup[i]->WealthPtr.ToSoftObjectPath().IsValid())
		{
			HFH::Debug() << ObjectName << " Get Not Vaild In Kind : " << WealthKind << " For Name : " << WealthEntrytGroup[i]->WealthName << HFH::Endl();
			return;
		}
		//��Դ����ƥ��
		if (WealthEntrytGroup[i]->WealthType != WealthType)
		{
			HFH::Debug() << ObjectName << " Get Error Type In Kind : " << WealthKind << " For Name : " << WealthEntrytGroup[i]->WealthName << HFH::Endl();
			return;
		}
	}
	//�ж�Transform�����Ƿ�Ϊ1�����Ƿ�ΪWealthEntrytGroup������
	if (WealthType == EWealthType::Actor && SpawnTransforms.Num() != 1 && SpawnTransforms.Num() != WealthEntrytGroup.Num())
	{
		HFH::Debug() << ObjectName << " Send Error Spawn Count : " << WealthKind << HFH::Endl();
		return;
	}
	//δ���ص���Դ����
	TArray<FClassWealthEntry*> UnLoadWealthEntry;
	//�Ѽ�����Դ����
	TArray<FClassWealthEntry*> LoadWealthEntry;
	//��Դ����
	for (int i = 0; i < WealthEntrytGroup.Num(); ++i)
	{
		if (WealthEntrytGroup[i]->WealthClass)
			LoadWealthEntry.Push(WealthEntrytGroup[i]);
		else
			UnLoadWealthEntry.Push(WealthEntrytGroup[i]);
	}
	//����һ�����ؾ��
	TSharedPtr<FStreamableHandle> WealthHandle;
	//�����δ���ص���Դ
	if (UnLoadWealthEntry.Num() > 0)
	{
		//��ȡ��Դ·��
		TArray<FSoftObjectPath> WealthPaths;
		for (int i = 0; i < UnLoadWealthEntry.Num(); ++i)
			WealthPaths.Push(UnLoadWealthEntry[i]->WealthPtr.ToSoftObjectPath());
		//��ȡ���ؾ��
		WealthHandle = WealthLoader.RequestAsyncLoad(WealthPaths);
	}
	//����֡����Ľڵ�
	ClassKindLoadStack.Push(new ClassKindLoadNode(WealthHandle, UnLoadWealthEntry, LoadWealthEntry, ObjectName, FuncName, SpawnTransforms));
}

void UHFWealth::BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName ObjectName, FName FuncName, TArray<FTransform> SpawnTransforms)
{
	//��ȡ��Ӧ����Դ�ṹ��
	FClassWealthEntry* WealthEntry = GetSingleClassEntry(WealthName);
	//���Ϊ��
	if (!WealthEntry)
	{
		HFH::Debug() << ObjectName << " Get Null Wealth : " << WealthName << HFH::Endl();
		return;
	}
	//�����Դ������
	if (!WealthEntry->WealthPtr.ToSoftObjectPath().IsValid())
	{
		HFH::Debug() << ObjectName << " Get UnValid Wealth : " << WealthName << HFH::Endl();
		return;
	}
	//��Դ�����Ƿ�ƥ��
	if (WealthEntry->WealthType != WealthType)
	{
		HFH::Debug() << ObjectName << " Get Error Type : " << WealthName << HFH::Endl();
		return;
	}
	//��֤Transform����������Ƿ�Ϊ1����Amount = 0
	if ((WealthType == EWealthType::Actor && SpawnTransforms.Num() != 1 && SpawnTransforms.Num() != Amount) || Amount == 0)
	{
		HFH::Debug() << ObjectName << " Send Error Spawn Count : " << WealthName << HFH::Endl();
		return;
	}
	//����Ѿ�������Դ
	if (WealthEntry->WealthClass)
		ClassMultiLoadStack.Push(new ClassMultiLoadNode(WealthEntry, Amount, ObjectName, FuncName, SpawnTransforms));
	else
	{
		//�첽����
		TSharedPtr<FStreamableHandle> WealthHandle = WealthLoader.RequestAsyncLoad(WealthEntry->WealthPtr.ToSoftObjectPath());
		//����½ڵ�
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
	//���������ɵ�����
	TArray<ObjectSingleLoadNode*> CompleteStack;
	for (int i = 0; i < ObjectSingleLoadStack.Num(); ++i)
	{
		//�ж��Ƿ��Ѿ��������
		if (ObjectSingleLoadStack[i]->WealthHandle->HasLoadCompleted())
		{
			//���ö�Ӧ��Դ���
			ObjectSingleLoadStack[i]->WealthEntry->WealthObj = ObjectSingleLoadStack[i]->WealthEntry->WealthPath.ResolveObject();
			//������Դ������
			BackCallObjWealth(ModuleIndex, ObjectSingleLoadStack[i]->ObjectName, ObjectSingleLoadStack[i]->FuncName,
				ObjectSingleLoadStack[i]->WealthEntry->WealthName, ObjectSingleLoadStack[i]->WealthEntry->WealthObj);
			//����Ѿ�������ɵĽڵ㵽��ʱ����
			CompleteStack.Push(ObjectSingleLoadStack[i]);
		}
	}
	//�����Ѿ���ɵĽڵ�
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ObjectSingleLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}

void UHFWealth::DealKindObjectLoadStack()
{
	//���������ɵ�����
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

	//�����Ѿ���ɵĽڵ�
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ObjectKindLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}

void UHFWealth::DealSingleClassLoadStack()
{
	//���������ɵ�����
	TArray<ClassSingleLoadNode*> CompleteStack;
	for (int i = 0; i < ClassSingleLoadStack.Num(); ++i)
	{
		//�ж��Ƿ��Ѿ��������
		if (ClassSingleLoadStack[i]->WealthHandle->HasLoadCompleted())
		{
			//���ö�Ӧ��Դ���
			ClassSingleLoadStack[i]->WealthEntry->WealthClass = Cast<UClass>(ClassSingleLoadStack[i]->WealthEntry->WealthPtr.ToSoftObjectPath().ResolveObject());
			//�ж��Ƿ����ɶ���
			if (ClassSingleLoadStack[i]->IsLoadClass)
			{
				//������Դ������
				BackCallClassWealth(ModuleIndex, ClassSingleLoadStack[i]->ObjectName, ClassSingleLoadStack[i]->FuncName,
					ClassSingleLoadStack[i]->WealthEntry->WealthName, ClassSingleLoadStack[i]->WealthEntry->WealthClass);
			}
			else
			{
				//���ɲ��Ҵ��ݶ���������
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
					//�������
					GCWidgetGroup.Push(InstWidget);
					BackCallWidgetSingle(ModuleIndex, ClassSingleLoadStack[i]->ObjectName, ClassSingleLoadStack[i]->FuncName,
						ClassSingleLoadStack[i]->WealthEntry->WealthName, InstWidget);
				}
			}
			
			//����Ѿ�������ɵĽڵ㵽��ʱ����
			CompleteStack.Push(ClassSingleLoadStack[i]);
		}
	}
	//�����Ѿ���ɵĽڵ�
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ClassSingleLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}

void UHFWealth::DealKindClassLoadStack()
{
	//��������ɼ��ؽڵ�����
	TArray<ClassKindLoadNode*> CompleteStack;
	for (int i = 0; i < ClassKindLoadStack.Num(); ++i)
	{
		//�жϵ�һ�μ������, WealthHandle�Ѿ��������, UnLoadWealthEntry��������0
		if (ClassKindLoadStack[i]->WealthHandle.IsValid() && ClassKindLoadStack[i]->WealthHandle->HasLoadCompleted() && ClassKindLoadStack[i]->UnLoadWealthEntry.Num() > 0)
		{
			//����Ѿ��������, ����δ�������е���Դָ��
			for (int j = 0; j < ClassKindLoadStack[i]->UnLoadWealthEntry.Num(); ++j)
				ClassKindLoadStack[i]->UnLoadWealthEntry[j]->WealthClass = Cast<UClass>(ClassKindLoadStack[i]->UnLoadWealthEntry[j]->WealthPtr.ToSoftObjectPath().ResolveObject());
			//��δ����������������Դ��䵽�Ѽ�����Դ����
			ClassKindLoadStack[i]->LoadedWealthEntry.Append(ClassKindLoadStack[i]->UnLoadWealthEntry);
			//���UnLoadWealthEntry
			ClassKindLoadStack[i]->UnLoadWealthEntry.Empty();
		}

		//���δ��������Ϊ0, ˵���Ѿ��������
		if (ClassKindLoadStack[i]->UnLoadWealthEntry.Num() == 0)
		{
			//����UClass����ֱ��������Դ�����������
			if (ClassKindLoadStack[i]->IsLoadClass)
			{
				//���÷������
				TArray<FName> NameGroup;
				TArray<UClass*> WealthGroup;
				for (int j = 0; j < ClassKindLoadStack[i]->LoadedWealthEntry.Num(); ++j)
				{
					NameGroup.Push(ClassKindLoadStack[i]->LoadedWealthEntry[j]->WealthName);
					WealthGroup.Push(ClassKindLoadStack[i]->LoadedWealthEntry[j]->WealthClass);
				}
				//������Դ���������
				BackCallClassWealthKind(ModuleIndex, ClassKindLoadStack[i]->ObjectName, ClassKindLoadStack[i]->FuncName, NameGroup, WealthGroup);
				//��Ӹýڵ㵽���������
				CompleteStack.Push(ClassKindLoadStack[i]);
			}
			else //���Ҫ���ɶ���
			{
				//���Ѽ��ص���Դ������ȡ����һ��
				FClassWealthEntry* WealthEntry = ClassKindLoadStack[i]->LoadedWealthEntry[0];
				//�Ƴ�������
				ClassKindLoadStack[i]->LoadedWealthEntry.RemoveAt(0);
				//������Դ�������ɶ���
				if (WealthEntry->WealthType == EWealthType::Object)
				{
					UObject* InstObject = NewObject<UObject>(this, WealthEntry->WealthClass);
					InstObject->AddToRoot();
					//����Ҳ�������
					ClassKindLoadStack[i]->NameGroup.Push(WealthEntry->WealthName);
					ClassKindLoadStack[i]->ObjectGroup.Push(InstObject);
					//�ж��Ƿ�������ȫ���Ķ���
					if (ClassKindLoadStack[i]->LoadedWealthEntry.Num() == 0)
					{
						//�������ߴ������ɵĶ���
						BackCallObjectKind(ModuleIndex, ClassKindLoadStack[i]->ObjectName, ClassKindLoadStack[i]->FuncName, ClassKindLoadStack[i]->NameGroup, ClassKindLoadStack[i]->ObjectGroup);
						//��ӵ��������
						CompleteStack.Push(ClassKindLoadStack[i]);
					}
				}
				else if (WealthEntry->WealthType == EWealthType::Actor)
				{
					//��ȡ����λ��
					FTransform SpawnTransform = ClassKindLoadStack[i]->SpawnTransforms.Num() == 1 ? ClassKindLoadStack[i]->SpawnTransforms[0] : ClassKindLoadStack[i]->SpawnTransforms[ClassKindLoadStack[i]->ActorGroup.Num()];
					//���ɶ���
					AActor* InstActor = GetHFWorld()->SpawnActor<AActor>(WealthEntry->WealthClass, SpawnTransform);
					//��ӵ���������
					ClassKindLoadStack[i]->NameGroup.Push(WealthEntry->WealthName);
					ClassKindLoadStack[i]->ActorGroup.Push(InstActor);
					//�ж��Ƿ�������ȫ���Ķ���
					if (ClassKindLoadStack[i]->LoadedWealthEntry.Num() == 0)
					{
						//�������ߴ������ɵĶ���
						BackCallActorKind(ModuleIndex, ClassKindLoadStack[i]->ObjectName, ClassKindLoadStack[i]->FuncName, ClassKindLoadStack[i]->NameGroup, ClassKindLoadStack[i]->ActorGroup);
						//��ӵ��������
						CompleteStack.Push(ClassKindLoadStack[i]);
					}
				}
				else if (WealthEntry->WealthType == EWealthType::Widget)
				{
					UUserWidget* InstWidget = CreateWidget<UUserWidget>(GetHFWorld(), WealthEntry->WealthClass);
					//�������
					GCWidgetGroup.Push(InstWidget);
					//��ӵ���������
					ClassKindLoadStack[i]->NameGroup.Push(WealthEntry->WealthName);
					ClassKindLoadStack[i]->WidgetGroup.Push(InstWidget);
					//�ж��Ƿ�������ȫ���Ķ���
					if (ClassKindLoadStack[i]->LoadedWealthEntry.Num() == 0)
					{
						//�������ߴ������ɵĶ���
						BackCallWidgetKind(ModuleIndex, ClassKindLoadStack[i]->ObjectName, ClassKindLoadStack[i]->FuncName, ClassKindLoadStack[i]->NameGroup, ClassKindLoadStack[i]->WidgetGroup);
						//��ӵ��������
						CompleteStack.Push(ClassKindLoadStack[i]);
					}
				}
			}
		}
	}
	//�������ɽڵ�
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ClassKindLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}

void UHFWealth::DealMultiClassLoadStack()
{
	//������ɵĽڵ�
	TArray<ClassMultiLoadNode*> CompleteStack;
	for (int i = 0; i < ClassMultiLoadStack.Num(); ++i)
	{
		//���û�м���UClass, ˵�����ؾ����Ч
		if (!ClassMultiLoadStack[i]->WealthEntry->WealthClass)
		{
			//������ؾ���������
			if (ClassMultiLoadStack[i]->WealthHandle->HasLoadCompleted())
				ClassMultiLoadStack[i]->WealthEntry->WealthClass = Cast<UClass>(ClassMultiLoadStack[i]->WealthHandle->GetLoadedAsset());
		}
		//�ٴ��ж�WealthClass�Ƿ����, ������ڽ������ɶ���׶�
		if (ClassMultiLoadStack[i]->WealthEntry->WealthClass)
		{
			//�����������ɶ�
			if (ClassMultiLoadStack[i]->WealthEntry->WealthType == EWealthType::Object)
			{
				UObject* InstObject = NewObject<UObject>(this, ClassMultiLoadStack[i]->WealthEntry->WealthClass);
				InstObject->AddToRoot();
				ClassMultiLoadStack[i]->ObjectGroup.Push(InstObject);
				//����������
				if (ClassMultiLoadStack[i]->ObjectGroup.Num() == ClassMultiLoadStack[i]->Amount)
				{
					//���ض����������
					BackCallObjectMulti(ModuleIndex, ClassMultiLoadStack[i]->ObjectName, ClassMultiLoadStack[i]->FuncName, ClassMultiLoadStack[i]->WealthEntry->WealthName, ClassMultiLoadStack[i]->ObjectGroup);
					//��ӵ��������
					CompleteStack.Push(ClassMultiLoadStack[i]);
				}
			}
			else if (ClassMultiLoadStack[i]->WealthEntry->WealthType == EWealthType::Actor)
			{
				//��ȡ����λ��
				FTransform SpawnTransform = ClassMultiLoadStack[i]->SpawnTransforms.Num() == 1 ? ClassMultiLoadStack[i]->SpawnTransforms[0] : ClassMultiLoadStack[i]->SpawnTransforms[ClassMultiLoadStack[i]->ActorGroup.Num()];
				//���ɶ���
				AActor* InstActor = GetHFWorld()->SpawnActor<AActor>(ClassMultiLoadStack[i]->WealthEntry->WealthClass, SpawnTransform);
				//��Ӳ�������
				ClassMultiLoadStack[i]->ActorGroup.Push(InstActor);
				//�ж��Ƿ�������ȫ���Ķ���
				if (ClassMultiLoadStack[i]->ActorGroup.Num() == ClassMultiLoadStack[i]->Amount)
				{
					//�������ߴ������ɵĶ���
					BackCallActorMulti(ModuleIndex, ClassMultiLoadStack[i]->ObjectName, ClassMultiLoadStack[i]->FuncName, ClassMultiLoadStack[i]->WealthEntry->WealthName, ClassMultiLoadStack[i]->ActorGroup);
					//��ӵ��������
					CompleteStack.Push(ClassMultiLoadStack[i]);
				}
			}
			else if (ClassMultiLoadStack[i]->WealthEntry->WealthType == EWealthType::Widget)
			{
				UUserWidget* InstWidget = CreateWidget<UUserWidget>(GetHFWorld(), ClassMultiLoadStack[i]->WealthEntry->WealthClass);
				//�������
				GCWidgetGroup.Push(InstWidget);
				//��Ӳ�������
				ClassMultiLoadStack[i]->WidgetGroup.Push(InstWidget);
				//�ж��Ƿ�������ȫ���Ķ���
				if (ClassMultiLoadStack[i]->WidgetGroup.Num() == ClassMultiLoadStack[i]->Amount)
				{
					//�������ߴ������ɵĶ���
					BackCallWidgetMulti(ModuleIndex, ClassMultiLoadStack[i]->ObjectName, ClassMultiLoadStack[i]->FuncName, ClassMultiLoadStack[i]->WealthEntry->WealthName, ClassMultiLoadStack[i]->WidgetGroup);
					//��ӵ��������
					CompleteStack.Push(ClassMultiLoadStack[i]);
				}
			}
		}
	}
	//�������ɽڵ�
	for (int i = 0; i < CompleteStack.Num(); ++i)
	{
		ClassMultiLoadStack.Remove(CompleteStack[i]);
		delete CompleteStack[i];
	}
}
