// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HFGTypes.generated.h"

#pragma region GamePart

UENUM()
enum class ERCGameModule : uint8
{
	Center = 0,			//中央模组
	HUD,				//UI模组，约定放在第二位
	Player,				//玩家模组
};

#pragma endregion

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFGTypes : public UObject
{
	GENERATED_BODY()
	
};
