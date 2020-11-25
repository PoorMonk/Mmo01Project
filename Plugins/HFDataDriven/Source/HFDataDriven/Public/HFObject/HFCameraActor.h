// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "HFOOInterface.h"
#include "HFCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API AHFCameraActor : public ACameraActor, public IHFOOInterface
{
	GENERATED_BODY()
	
public:
	AHFCameraActor();

	virtual void HFRelease() override;

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
