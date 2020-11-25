// Fill out your copyright notice in the Description page of Project Settings.


#include "HFObject/HFPawn.h"

// Sets default values
AHFPawn::AHFPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AHFPawn::HFRelease()
{
	IHFOOInterface::HFRelease();

	GetHFWorld()->DestroyActor(this);
}

// Called when the game starts or when spawned
void AHFPawn::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterToModule(ModuleName, ObjectName, ClassName);
}


