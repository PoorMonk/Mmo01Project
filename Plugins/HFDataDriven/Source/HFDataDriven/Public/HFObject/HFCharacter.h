// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HFOOInterface.h"
#include "HFCharacter.generated.h"

UCLASS()
class HFDATADRIVEN_API AHFCharacter : public ACharacter, public IHFOOInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHFCharacter();

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
