// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HFOOInterface.h"
#include "HFObject.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFObject : public UObject, public IHFOOInterface
{
	GENERATED_BODY()
	
public:
	virtual void HFRelease() override;

};
