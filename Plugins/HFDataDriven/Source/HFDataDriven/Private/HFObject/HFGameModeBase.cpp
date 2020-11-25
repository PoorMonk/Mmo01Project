// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFGameModeBase.h"

AHFGameModeBase::AHFGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHFGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	RegisterToModule(ModuleName, ObjectName, ClassName);
}
