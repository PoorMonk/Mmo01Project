// Fill out your copyright notice in the Description page of Project Settings.


#include "HFCore/HFMMInterface.h"
#include "HFCore/HFModule.h"
#include "HFCore/HFDriver.h"

// Add default functionality here for any IHFMMInterface functions that are not pure virtual.

void IHFMMInterface::AssignModule(UHFModule* Mod)
{
	IModule = Mod;
	ModuleIndex = IModule->ModuleIndex;
	IDriver = UHFCommon::Get()->GetDriver();
}

void IHFMMInterface::ExecuteFunction(HFModuleAgreement Agreement, HFParam* Param)
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

void IHFMMInterface::ExecuteFunction(HFObjectAgreement Agreement, HFParam* Param)
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

UWorld* IHFMMInterface::GetHFWorld() const
{
	if (IDriver)
	{
		return IDriver->GetWorld();
	}
	return nullptr;
}
