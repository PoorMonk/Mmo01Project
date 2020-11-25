// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFCharacter.h"

// Sets default values
AHFCharacter::AHFCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AHFCharacter::HFRelease()
{
	IHFOOInterface::HFRelease();

	GetHFWorld()->DestroyActor(this);
}

// Called when the game starts or when spawned
void AHFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterToModule(ModuleName, ObjectName, ClassName);
}

