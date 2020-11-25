// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HFOOInterface.h"
#include "HFUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFUserWidget : public UUserWidget, public IHFOOInterface
{
	GENERATED_BODY()
	
public:
	virtual void HFRelease() override;

};
