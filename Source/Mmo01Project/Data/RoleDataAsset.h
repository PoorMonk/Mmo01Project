// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RoleDataAsset.generated.h"

class UTexture;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API URoleDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<UTexture*> RoleTextures;
};
