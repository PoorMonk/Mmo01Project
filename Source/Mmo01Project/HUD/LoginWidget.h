// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

class UButton;
class UEditableTextBox;
class ALoginGameMode;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnBtnLoginClicked();

	UFUNCTION(BlueprintCallable)
	void OnBtnRegisterClicked();

public:

	ALoginGameMode* MmoLoginGameMode;

protected:
	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_Login;

	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_Register;

	UPROPERTY(Meta = (BindWidget))
	UEditableTextBox* EditText_Username;

	UPROPERTY(Meta = (BindWidget))
	UEditableTextBox* EditText_Password;

private:

	void RegisterOrLogin(bool isLogin);

	bool GetInfo(FString& userName, FString& passWord, TArray<uint8>& datas);
};
