// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFCameraActor.h"

AHFCameraActor::AHFCameraActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHFCameraActor::HFRelease()
{
	IHFOOInterface::HFRelease();

	GetHFWorld()->DestroyActor(this);
}

void AHFCameraActor::BeginPlay()
{
	Super::BeginPlay();

	RegisterToModule(ModuleName, ObjectName, ClassName);
}
