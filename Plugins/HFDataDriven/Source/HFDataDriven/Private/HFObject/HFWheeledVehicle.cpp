// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFWheeledVehicle.h"

AHFWheeledVehicle::AHFWheeledVehicle()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHFWheeledVehicle::HFRelease()
{
	IHFOOInterface::HFRelease();

	GetHFWorld()->DestroyActor(this);
}

void AHFWheeledVehicle::BeginPlay()
{
	Super::BeginPlay();

	RegisterToModule(ModuleName, ObjectName, ClassName);
}
