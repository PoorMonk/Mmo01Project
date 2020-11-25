// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/HFObject/HFOOInterface.h"
#include "HFCommon/HFCommon.h"

// Add default functionality here for any IHFOOInterface functions that are not pure virtual.

void IHFOOInterface::RegisterToModule(FName ModName, FName ObjName /*= FName()*/, FName ClsName /*= FName()*/)
{
	if (ModName.IsNone())
	{
		return;
	}
	RegisterInit(ObjName, ClsName);
	int32 ModIndex = -1;
	if (IDriver)
	{
		ModIndex = HFH::GetEnumIndexFromName(IDriver->ModuleType.ToString(), ModName);
	}
	Register(ModIndex);
}

void IHFOOInterface::RegisterToModule(int32 ModIndex, FName ObjName /*= FName()*/, FName ClsName /*= FName()*/)
{
	RegisterInit(ObjName, ClsName);
	Register(ModIndex);
}


void IHFOOInterface::RegisterInit(FName ObjName /*= FName()*/, FName ClsName /*= FName()*/)
{
	//如果已经注册或者模组名为空
	if (IDriver && IModule)
	{
		return;
	}

	if (!ObjName.IsNone())
	{
		IObjectName = ObjName;
	}
	if (!ClsName.IsNone())
	{
		IClassName = ClsName;
	}
	IBody = Cast<UObject>(this);
	IDriver = UHFCommon::Get()->GetDriver();
}


void IHFOOInterface::Register(int32 ModIndex)
{
	if (IDriver)
	{
		ModuleIndex = ModIndex;
		if (ModuleIndex < 0)
		{
			HFH::Debug() << GetObjectName() << " Get " << ModIndex << " ModuleIndex Failed!" << HFH::Endl();
			return;
		}
		if (!IDriver->RegisterToModule(this))
		{
			HFH::Debug() << GetObjectName() << " Register To " << ModIndex << " Failed!" << HFH::Endl();
		}
	}
	else
	{
		HFH::Debug() << GetObjectName() << " Get HFDriver Failed!" << HFH::Endl();
	}
}

FName IHFOOInterface::GetObjectName() const
{
	return IObjectName.IsNone() ? IBody->GetFName() : IObjectName;
}

FName IHFOOInterface::GetClassName() const
{
	return IClassName.IsNone() ? IBody->GetClass()->GetFName() : IClassName;
}

int32 IHFOOInterface::GetModuleIndex() const
{
	return ModuleIndex;
}

UObject* IHFOOInterface::GetObjectBody() const
{
	return IBody;
}

UWorld* IHFOOInterface::GetHFWorld() const
{
	if (IDriver)
	{
		return IDriver->GetWorld();
	}
	return nullptr;
}

void IHFOOInterface::AssignModule(UHFModule* Mod)
{
	IModule = Mod;
}

bool IHFOOInterface::ActiveLife()
{
	switch (LifeState)
	{
	case EBaseObjectLife::None:
		HFInit();
		LifeState = EBaseObjectLife::Init;
		break;
	case EBaseObjectLife::Init:
		HFLoading();
		LifeState = EBaseObjectLife::Loading;
		break;
	case EBaseObjectLife::Loading:
		HFRegister();
		LifeState = EBaseObjectLife::Register;
		break;
	case EBaseObjectLife::Register:
		HFEnable();
		LifeState = EBaseObjectLife::Enable;
		RunState = EBaseObjectState::Stable;
		return true;
	}
	return false;
}

bool IHFOOInterface::DestroyLife()
{
	switch (LifeState)
	{
	case EBaseObjectLife::Enable:
		HFDisable();
		LifeState = EBaseObjectLife::Disable;
		RunState = EBaseObjectState::Destroy;
		break;
	case EBaseObjectLife::Disable:
		HFUnRegister();
		LifeState = EBaseObjectLife::UnRegister;
		RunState = EBaseObjectState::Destroy;
		break;
	case EBaseObjectLife::UnRegister:
		HFUnLoading();
		LifeState = EBaseObjectLife::UnLoading;
		return true;
	}
	return false;
}

void IHFOOInterface::HFInit()
{

}

void IHFOOInterface::HFLoading()
{

}

void IHFOOInterface::HFRegister()
{

}

void IHFOOInterface::HFEnable()
{

}

void IHFOOInterface::HFTick(float DeltaSeconds)
{

}

void IHFOOInterface::HFDisable()
{

}

void IHFOOInterface::HFUnRegister()
{

}

void IHFOOInterface::HFUnLoading()
{

}

void IHFOOInterface::HFRelease()
{

}

void IHFOOInterface::OnEnable()
{
	LifeState = EBaseObjectLife::Enable;
}

void IHFOOInterface::OnDisable()
{
	LifeState = EBaseObjectLife::Disable;
}

void IHFOOInterface::HFDestroy()
{
	IModule->ChildDestroy(GetObjectName());
}

void IHFOOInterface::ExecuteFunction(HFModuleAgreement Agreement, HFParam* Param)
{
	if (Agreement.ModuleIndex == ModuleIndex)
	{
		IModule->ExecuteFunction(Agreement, Param);
	}
	else
	{
		IDriver->ExecuteFunction(Agreement, Param);
	}
}

void IHFOOInterface::ExecuteFunction(HFObjectAgreement Agreement, HFParam* Param)
{
	if (Agreement.ModuleIndex == ModuleIndex)
	{
		IModule->ExecuteFunction(Agreement, Param);
	}
	else
	{
		IDriver->ExecuteFunction(Agreement, Param);
	}
}

FWealthURL* IHFOOInterface::GainWealthURL(FName WealthName)
{
	return IModule->GainWealthURL(WealthName);
}

void IHFOOInterface::GainWealthURL(FName WealthKind, TArray<FWealthURL*>& OutURL)
{
	IModule->GainWealthURL(WealthKind, OutURL);
}

void IHFOOInterface::LoadObjectWealth(FName WealthName, FName FuncName)
{
	IModule->LoadObjectWealth(WealthName, GetObjectName(), FuncName);
}

void IHFOOInterface::LoadObjectWealthKind(FName WealthKind, FName FuncName)
{
	IModule->LoadObjectWealthKind(WealthKind, GetObjectName(), FuncName);
}

void IHFOOInterface::LoadUClassWealth(FName WealthName, FName FuncName)
{
	IModule->LoadUClassWealth(WealthName, GetObjectName(), FuncName);
}

void IHFOOInterface::LoadUClassWealthKind(FName WealthKind, FName FuncName)
{
	IModule->LoadUClassWealthKind(WealthKind, GetObjectName(), FuncName);
}

void IHFOOInterface::BuildSingleClassWealth(EWealthType WealthType, FName WealthName, FName FuncName, FTransform SpawnTransform)
{
	IModule->BuildSingleClassWealth(WealthType, WealthName, GetObjectName(), FuncName, SpawnTransform);
}

void IHFOOInterface::BuildSingleClassWealth(EWealthType WealthType, FName WealthName, FName FuncName)
{
	IModule->BuildSingleClassWealth(WealthType, WealthName, GetObjectName(), FuncName, FTransform::Identity);
}

void IHFOOInterface::BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName FuncName, TArray<FTransform> SpawnTransforms)
{
	IModule->BuildKindClassWealth(WealthType, WealthKind, GetObjectName(), FuncName, SpawnTransforms);
}

void IHFOOInterface::BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName FuncName)
{
	IModule->BuildKindClassWealth(WealthType, WealthKind, GetObjectName(), FuncName, TArray<FTransform> { FTransform::Identity});
}

void IHFOOInterface::BuildKindClassWealth(EWealthType WealthType, FName WealthKind, FName FuncName, FTransform SpawnTransforms)
{
	IModule->BuildKindClassWealth(WealthType, WealthKind, GetObjectName(), FuncName, TArray<FTransform> { SpawnTransforms});
}

void IHFOOInterface::BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amout, FName FuncName, TArray<FTransform> SpawnTransforms)
{
	IModule->BuildMultiClassWealth(WealthType, WealthName, Amout, GetObjectName(), FuncName, SpawnTransforms);
}

void IHFOOInterface::BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName FuncName)
{
	IModule->BuildMultiClassWealth(WealthType, WealthName, Amount, GetObjectName(), FuncName, TArray<FTransform> { FTransform::Identity});
}

void IHFOOInterface::BuildMultiClassWealth(EWealthType WealthType, FName WealthName, int32 Amount, FName FuncName, FTransform SpawnTransform)
{
	IModule->BuildMultiClassWealth(WealthType, WealthName, Amount, GetObjectName(), FuncName, TArray<FTransform> { SpawnTransform});
}
