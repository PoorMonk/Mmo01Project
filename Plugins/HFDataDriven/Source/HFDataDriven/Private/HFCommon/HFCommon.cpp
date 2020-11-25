// Fill out your copyright notice in the Description page of Project Settings.


#include "HFCommon/HFCommon.h"

UHFCommon* UHFCommon::HFComInst = nullptr;

UHFCommon* UHFCommon::Get()
{
	if (!HFComInst)
	{
		HFComInst = NewObject<UHFCommon>();
		HFComInst->AddToRoot();
	}

	return HFComInst;
}

void UHFCommon::InitDriver(AHFDriver* InDriver)
{
	Driver = InDriver;
}

AHFDriver* UHFCommon::GetDriver()
{
	return Driver;
}

void UHFCommon::InitController(APlayerController* InController)
{
	PlayerController = InController;
}

APlayerController* UHFCommon::GetController()
{
	return PlayerController;
}

void UHFCommon::SetPauseGame(bool IsPause)
{
	PlayerController->SetPause(IsPause);
}

const bool UHFCommon::IsPauseGame() const
{
	return PlayerController->IsPaused();
}

