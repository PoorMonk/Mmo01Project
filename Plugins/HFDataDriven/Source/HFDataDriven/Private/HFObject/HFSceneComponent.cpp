// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFSceneComponent.h"

// Sets default values for this component's properties
UHFSceneComponent::UHFSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	bAllowAnyoneToDestroyMe = true;
}


void UHFSceneComponent::HFRelease()
{
	IHFOOInterface::HFRelease();

	DestroyComponent();
}

// Called when the game starts
void UHFSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	//×Ô¶¯×¢²áµ½¿ò¼Ü
	RegisterToModule(ModuleName, ObjectName, ClassName);
}


