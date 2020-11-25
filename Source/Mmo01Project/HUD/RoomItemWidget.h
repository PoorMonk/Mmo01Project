// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomItemWidget.generated.h"

class UOverlay;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API URoomItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowUI(uint32 type);

protected:
	UPROPERTY(Meta = (BindWidget))
	UOverlay* Overlay_Room1;

	UPROPERTY(Meta = (BindWidget))
	UOverlay* Overlay_Room2;
};
