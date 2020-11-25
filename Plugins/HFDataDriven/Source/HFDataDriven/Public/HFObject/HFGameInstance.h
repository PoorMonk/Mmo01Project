// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HFOOInterface.h"
#include "HFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFGameInstance : public UGameInstance, public IHFOOInterface
{
	GENERATED_BODY()
	
};
