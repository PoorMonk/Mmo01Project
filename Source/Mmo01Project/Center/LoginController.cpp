// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginController.h"

void ALoginController::BeginPlay()
{
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
	
	bShowMouseCursor = true;

	// ������Ϸ���ڴ�С
	ConsoleCommand(FString::Printf(TEXT("r.setres %dx%dw"), ScreenWidth, ScreenHeight));
}
