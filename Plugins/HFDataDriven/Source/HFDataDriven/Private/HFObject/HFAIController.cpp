// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFAIController.h"

AHFAIController::AHFAIController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHFAIController::BeginPlay()
{
	Super::BeginPlay();

	RegisterToModule(ModuleName, ObjectName, ClassName);
}
