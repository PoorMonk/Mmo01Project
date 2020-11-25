// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFPlayerController.h"

AHFPlayerController::AHFPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//×Ô¶¯×¢²áµ½¿ò¼Ü
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
