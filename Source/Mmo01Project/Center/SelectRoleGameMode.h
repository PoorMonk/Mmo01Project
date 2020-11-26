// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/KbeBaseGameMode.h"
#include "SelectRoleGameMode.generated.h"

class USelectRoleWidget;
class ARoleRenderActor;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API ASelectRoleGameMode : public AKbeBaseGameMode
{
	GENERATED_BODY()

public:

	virtual void InstallEvent() override;
	virtual void UnInstallEvent() override;

	virtual void BeginPlay() override;

	// 玩家进入游戏场景
	void AddSpaceGeometryMapping(const UKBEventData* EventData);

public:
	ARoleRenderActor* RoleRenderActor;

protected:
	void OnReqRoleList(const UKBEventData* pEventData);
	void OnSelectRole(const UKBEventData* pEventData);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<USelectRoleWidget> SelectRoleClass;

	USelectRoleWidget* MmoSelectRoleWidget;
	
	
};
