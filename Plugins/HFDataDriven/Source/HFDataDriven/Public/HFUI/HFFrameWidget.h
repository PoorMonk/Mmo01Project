// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HFObject/HFUserWidget.h"
#include "HFFrameWidget.generated.h"

class UCanvasPanel;
class UImage;
class UOverlay;
class UHFPanelWidget;

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFFrameWidget : public UHFUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	//提前加载UI
	UFUNCTION()
		void AdvanceLoadPanel(FName PanelName);

	//显示面板
	UFUNCTION()
		void ShowUIPanel(FName PanelName);

	//显示面板
	UFUNCTION()
		void HideUIPanel(FName PanelName);

	//显示面板
	UFUNCTION()
		void ExitUIPanel(FName PanelName);

	//提前加载面板回调函数
	UFUNCTION()
		void AcceptedAdvancePanel(FName BackcallName, UUserWidget* BackcallWidget);

	//显示时加载的回调函数
	UFUNCTION()
		void AccepPanelWidget(FName BackcallName, UUserWidget* BackcallWidget);

	//处理UI面板销毁后的父控件
	UFUNCTION()
		void ExitCallBack(ELayoutType LayoutType, UPanelWidget* InLayout);

protected:
	//执行进入UI
	void DoEnterUIPanel(FName PanelName);

	//执行显示UI
	void DoShowUIPanel(FName PanelName);

	//正在预加载，等待完成
	void WaitShowPanel();

	//第一次进入界面
	void EnterPanelDoNothing(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget);
	void EnterPanelDoNothing(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget);

	void EnterPanelHideOther(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget);
	void EnterPanelHideOther(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget);

	void EnterPanelReverse(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget);
	void EnterPanelReverse(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget);

	//激活遮罩
	void ActiveMask(UCanvasPanel* WorkLayout, EPanelLucenyType LucenyType);
	void ActiveMask(UOverlay* WorkLayout, EPanelLucenyType LucenyType);

	void RemoveMaskPanel(UPanelWidget* WorkLayout = nullptr);

protected:
	//根节点
	UCanvasPanel* RootCanvas;

	//保存Overlay控件
	UPROPERTY()
	TArray<UOverlay*> ActiveOverlay;
	UPROPERTY()
	TArray<UOverlay*> UnActiveOverlay;

	//保存Canvas控件
	UPROPERTY()
	TArray<UCanvasPanel*> ActiveCanvas;
	UPROPERTY()
	TArray<UCanvasPanel*> UnActiveCanvas;

	//所有UI面板,键必须是改面板注册到框架的ObjectName
	UPROPERTY()
	TMap<FName, UHFPanelWidget*> AllPanelGroup;

	//已经显示的UI
	UPROPERTY()
	TMap<FName, UHFPanelWidget*> ShowPanelGroup;

	//弹窗栈
	UPROPERTY()
	TMap<FName, UHFPanelWidget*> PopPanelStack;

	//已经加载过的UI面板的名字
	UPROPERTY()
	TArray<FName> LoadedPanelName;

	TArray<FName> WaitShowPanelName;

	//遮罩图片
	UPROPERTY()
		UImage* MaskPanel;

	//透明度值
	FLinearColor NormalLucency;
	FLinearColor TranslucenceLucency;
	FLinearColor ImPenetrableLucency;

	//保存循环检测加载完毕则显示方法的延时循环任务名字
	FName WaitShowTaskName;

private:
	//接收回调的UI面板
	void AcceptUIPanel(FName PanelName, UUserWidget* PanelWidget);

private:
	FTimerHandle WaitShowHandle;
};
