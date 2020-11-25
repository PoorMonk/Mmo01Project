// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFObject/HFUserWidget.h"
#include "HFPanelWidget.generated.h"



/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFPanelWidget : public UHFUserWidget
{
	GENERATED_BODY()
	
public:
	//UI面板生命周期
	virtual void PanelEnter();		//第一次进入界面，只会执行一次
	virtual void PanelDisplay();	//显示已存在界面
	virtual void PanelHidden();		//隐藏
	virtual void PanelFreeze();		//冻结
	virtual void PanelResume();		//恢复
	virtual void PanelExit();		//销毁

	//动画回调函数
	UFUNCTION(BlueprintImplementableEvent)
		float DisplayEnterMovie();

	UFUNCTION(BlueprintImplementableEvent)
		float DisplayLeaveMovie();

public:
	UPROPERTY(EditAnywhere)
		FUINature UINature;

protected:

	void SetSelfHidden();

private:
	FTimerHandle HideHandle;
};
