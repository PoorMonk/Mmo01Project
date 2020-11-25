// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/KbeBaseGameMode.h"
#include "LoginGameMode.generated.h"

class ULoginWidget;
class UKBEMain;

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API ALoginGameMode : public AKbeBaseGameMode
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void InstallEvent() override;

	virtual void UnInstallEvent() override;

	void OnCreateAccountResult(const UKBEventData* pEventData);
	void OnLoginFailed(const UKBEventData* pEventData);
	void OnVersionNotMatch(const UKBEventData* pEventData);
	void OnScriptVersionNotMatch(const UKBEventData* pEventData);
	void OnLoginBaseappFailed(const UKBEventData* pEventData);
	void OnLoginBaseapp(const UKBEventData* pEventData);

	void OnLoginSuccessfully(const UKBEventData* pEventData);

public:
	UKBEMain* KbeMain;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<ULoginWidget> LoginWidgetClass;

	ULoginWidget* MmoLoginWidget;

	
};
