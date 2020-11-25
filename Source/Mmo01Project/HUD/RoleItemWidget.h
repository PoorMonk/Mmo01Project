// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoleItemWidget.generated.h"

class UImage;

DECLARE_DELEGATE_OneParam(FRoleClickedDele, FString)

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API URoleItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void InitWidget(FString name, UTexture2D* texture);
	void ShowMask(bool bShow);

	UFUNCTION(BlueprintCallable)
	void OnBtnDownEvent();

public:

	FString RoleName;
	FRoleClickedDele RoleClickedDele;

protected:

	UPROPERTY(Meta = (BindWidget))
	UImage* Img_Mask;

	UPROPERTY(Meta = (BindWidget))
	UImage* Img_Role;
};
