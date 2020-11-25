// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/KbeBaseGameMode.h"
#include "SelectRoomGameMode.generated.h"

class USelectRoomWidget;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API ASelectRoomGameMode : public AKbeBaseGameMode
{
	GENERATED_BODY()
	
public:
	virtual void InstallEvent() override;

	virtual void BeginPlay() override;

protected:
	void OnReqRoomList(const UKBEventData* pEventData);
	void OnSelectRoom(const UKBEventData* pEventData);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<USelectRoomWidget> SelectRoomClass;

	USelectRoomWidget* SelRoomWidget;
};
