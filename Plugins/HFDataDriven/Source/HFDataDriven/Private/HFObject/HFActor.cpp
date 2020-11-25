// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFActor.h"

// Sets default values
AHFActor::AHFActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AHFActor::HFRelease()
{
	IHFOOInterface::HFRelease();

	GetHFWorld()->DestroyActor(this);
}

// Called when the game starts or when spawned
void AHFActor::BeginPlay()
{
	Super::BeginPlay();
	
	//×Ô¶¯×¢²áµ½¿ò¼Ü
	RegisterToModule(ModuleName, ObjectName, ClassName);
}


