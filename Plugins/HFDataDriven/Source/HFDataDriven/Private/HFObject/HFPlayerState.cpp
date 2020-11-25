// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFPlayerState.h"

AHFPlayerState::AHFPlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHFPlayerState::BeginPlay()
{
	Super::BeginPlay();

	//×Ô¶¯×¢²áµ½¿ò¼Ü
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
