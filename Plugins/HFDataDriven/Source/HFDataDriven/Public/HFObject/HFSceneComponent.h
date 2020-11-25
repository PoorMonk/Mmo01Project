// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HFOOInterface.h"
#include "HFSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HFDATADRIVEN_API UHFSceneComponent : public USceneComponent, public IHFOOInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHFSceneComponent();

	virtual void HFRelease() override;

public:
	UPROPERTY(EditAnywhere, Category = "HFDataDriven")
		FName ModuleName;

	UPROPERTY(EditAnywhere, Category = "HFDataDriven")
		FName ObjectName;

	UPROPERTY(EditAnywhere, Category = "HFDataDriven")
		FName ClassName;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
