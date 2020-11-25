// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "HFOOInterface.h"
#include "HFPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API AHFPlayerCameraManager : public APlayerCameraManager, public IHFOOInterface
{
	GENERATED_BODY()

public:
	AHFPlayerCameraManager();
	
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
