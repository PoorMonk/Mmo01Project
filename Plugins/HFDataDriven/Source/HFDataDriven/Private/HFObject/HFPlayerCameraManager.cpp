// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFPlayerCameraManager.h"

AHFPlayerCameraManager::AHFPlayerCameraManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHFPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	//×Ô¶¯×¢²áµ½¿ò¼Ü
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
