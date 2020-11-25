// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFGameStateBase.h"

AHFGameStateBase::AHFGameStateBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHFGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	//×Ô¶¯×¢²áµ½¿ò¼Ü
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
