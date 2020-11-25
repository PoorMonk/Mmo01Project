// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFHUD.h"

AHFHUD::AHFHUD()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHFHUD::BeginPlay()
{
	Super::BeginPlay();

	//×Ô¶¯×¢²áµ½¿ò¼Ü
	RegisterToModule(ModuleName, ObjectName, ClassName);
}
