// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFActorComponent.h"

// Sets default values for this component's properties
UHFActorComponent::UHFActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	bAllowAnyoneToDestroyMe = true;
}


void UHFActorComponent::HFRelease()
{
	IHFOOInterface::HFRelease();

	DestroyComponent();
}

// Called when the game starts
void UHFActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	RegisterToModule(ModuleName, ObjectName, ClassName);
}

