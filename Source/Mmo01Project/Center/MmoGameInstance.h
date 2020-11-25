// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MmoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API UMmoGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	uint64 RoomId;
};
