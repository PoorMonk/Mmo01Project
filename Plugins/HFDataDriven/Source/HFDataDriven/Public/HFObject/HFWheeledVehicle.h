// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "HFOOInterface.h"
#include "HFWheeledVehicle.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API AHFWheeledVehicle : public AWheeledVehicle, public IHFOOInterface
{
	GENERATED_BODY()

public:
	AHFWheeledVehicle();

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
