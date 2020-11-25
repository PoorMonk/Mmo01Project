// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginController.generated.h"

/**
 * 
 */
UCLASS()
class MMO01PROJECT_API ALoginController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//ALoginController();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "ScreenSize")
	int32 ScreenWidth;

	UPROPERTY(EditAnywhere, Category = "ScreenSize")
	int32 ScreenHeight;
};
