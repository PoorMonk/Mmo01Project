// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KBEnginePlugins/Scripts/MmoEventData.h"
#include "SelectRoleWidget.generated.h"

class ASelectRoleGameMode;
class URoleItemWidget;
class USizeBox;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API USelectRoleWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void InitRoleListUI();

	void RoleItemClickedDele(FString RoleName);

	UFUNCTION(BlueprintCallable)
	void OnEnterGameBtnClicked();

public:

	ASelectRoleGameMode* MmoSelectRoleGamemode;

	UPROPERTY()
	TArray<FROLE_INFO> RoleList;

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<URoleItemWidget> RoleItemClass;

	TMap<FString, URoleItemWidget*> RoleItemGroup;

	UPROPERTY(Meta = (BindWidget))
	USizeBox* RoleOneSizeBox;
	UPROPERTY(Meta = (BindWidget))
	USizeBox* RoleTwoSizeBox;

	uint64 Dbid;
};
