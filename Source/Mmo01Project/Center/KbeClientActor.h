// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KbeClientActor.generated.h"

class UKBEMain;

UCLASS()
class MMO01PROJECT_API AKbeClientActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKbeClientActor();

public:
	UPROPERTY(EditDefaultsOnly, Category = "KBEngine")
	UKBEMain* KbeMain;
};
