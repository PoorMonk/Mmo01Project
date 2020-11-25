// Fill out your copyright notice in the Description page of Project Settings.


#include "KbeClientActor.h"
#include "../Plugins/kbengine_ue4_plugins/Source/KBEnginePlugins/Engine/KBEMain.h"
//#include "../Engine/KBEMain.h"

// Sets default values
AKbeClientActor::AKbeClientActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	KbeMain = CreateDefaultSubobject<UKBEMain>(TEXT("KbeMain"));
}



