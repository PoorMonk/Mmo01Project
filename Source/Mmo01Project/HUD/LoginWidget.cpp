// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Button.h"
#include "EditableTextBox.h"
#include "HFDataDriven/Public/HFCommon/HFCommon.h"
#include "Center/LoginGameMode.h"
#include "KBEnginePlugins/Engine/KBEMain.h"

void ULoginWidget::OnBtnLoginClicked()
{
	RegisterOrLogin(true);
}

void ULoginWidget::OnBtnRegisterClicked()
{
	RegisterOrLogin(false);
}

void ULoginWidget::RegisterOrLogin(bool isLogin)
{
	FString username = EditText_Username->GetText().ToString();;
	FString password = EditText_Password->GetText().ToString();;
	TArray<uint8> Params;
	
	if (username.IsEmpty() || password.IsEmpty())
	{
		HFH::Debug() << "username or password is null" << HFH::Endl();
		return;
	}

	FString name = "MmoProject";
	for (int i = 0; i < name.Len(); ++i)
	{
		Params.Add((uint8)name[i]);
	}

	if (isLogin)
	{
		MmoLoginGameMode->KbeMain->login(username, password, Params);
	}
	else
	{
		MmoLoginGameMode->KbeMain->createAccount(username, password, Params);
	}
}

