// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoleRenderActor.generated.h"

UCLASS()
class MMO01PROJECT_API ARoleRenderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoleRenderActor();

	UFUNCTION(BlueprintImplementableEvent)
	void SwitchRoleMesh(int32 type);
};
