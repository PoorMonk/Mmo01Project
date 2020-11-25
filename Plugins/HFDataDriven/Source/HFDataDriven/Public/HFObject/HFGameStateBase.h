// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HFOOInterface.h"
#include "HFGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API AHFGameStateBase : public AGameStateBase, public IHFOOInterface
{
	GENERATED_BODY()
	
public:
	AHFGameStateBase();

public:
	UPROPERTY(EditAnywhere, Category = "HFDataDriven")
		FName ModuleName;

	UPROPERTY(EditAnywhere, Category = "HFDataDriven")
		FName ObjectName;

	UPROPERTY(EditAnywhere, Category = "HFDataDriven")
		FName ClassName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
