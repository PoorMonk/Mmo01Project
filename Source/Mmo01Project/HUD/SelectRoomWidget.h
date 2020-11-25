// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KBEnginePlugins/Scripts/MmoEventData.h"
#include "SelectRoomWidget.generated.h"

class ASelectRoomGameMode;
class URoomItemWidget;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API USelectRoomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnLeftBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnRightBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnConfirmBtnClicked();

public:

	ASelectRoomGameMode* SelRoomGameMode;

	UPROPERTY()
	TArray<FROOM_INFO> RoomList;

protected:
	UPROPERTY(Meta = (BindWidget))
	URoomItemWidget* UMG_RoomItem;

	int32 currRoom;
};
