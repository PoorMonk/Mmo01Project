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

	//��ǰ����UI
	UFUNCTION()
		void AdvanceLoadPanel(FName PanelName);

	//��ʾ���
	UFUNCTION()
		void ShowUIPanel(FName PanelName);

	//��ʾ���
	UFUNCTION()
		void HideUIPanel(FName PanelName);

	//��ʾ���
	UFUNCTION()
		void ExitUIPanel(FName PanelName);

	//��ǰ�������ص�����
	UFUNCTION()
		void AcceptedAdvancePanel(FName BackcallName, UUserWidget* BackcallWidget);

	//��ʾʱ���صĻص�����
	UFUNCTION()
		void AccepPanelWidget(FName BackcallName, UUserWidget* BackcallWidget);

	//����UI������ٺ�ĸ��ؼ�
	UFUNCTION()
		void ExitCallBack(ELayoutType LayoutType, UPanelWidget* InLayout);

protected:
	//ִ�н���UI
	void DoEnterUIPanel(FName PanelName);

	//ִ����ʾUI
	void DoShowUIPanel(FName PanelName);

	//����Ԥ���أ��ȴ����
	void WaitShowPanel();

	//��һ�ν������
	void EnterPanelDoNothing(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget);
	void EnterPanelDoNothing(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget);

	void EnterPanelHideOther(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget);
	void EnterPanelHideOther(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget);

	void EnterPanelReverse(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget);
	void EnterPanelReverse(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget);

	//��������
	void ActiveMask(UCanvasPanel* WorkLayout, EPanelLucenyType LucenyType);
	void ActiveMask(UOverlay* WorkLayout, EPanelLucenyType LucenyType);

	void RemoveMaskPanel(UPanelWidget* WorkLayout = nullptr);

protected:
	//���ڵ�
	UCanvasPanel* RootCanvas;

	//����Overlay�ؼ�
	UPROPERTY()
	TArray<UOverlay*> ActiveOverlay;
	UPROPERTY()
	TArray<UOverlay*> UnActiveOverlay;

	//����Canvas�ؼ�
	UPROPERTY()
	TArray<UCanvasPanel*> ActiveCanvas;
	UPROPERTY()
	TArray<UCanvasPanel*> UnActiveCanvas;

	//����UI���,�������Ǹ����ע�ᵽ��ܵ�ObjectName
	UPROPERTY()
	TMap<FName, UHFPanelWidget*> AllPanelGroup;

	//�Ѿ���ʾ��UI
	UPROPERTY()
	TMap<FName, UHFPanelWidget*> ShowPanelGroup;

	//����ջ
	UPROPERTY()
	TMap<FName, UHFPanelWidget*> PopPanelStack;

	//�Ѿ����ع���UI��������
	UPROPERTY()
	TArray<FName> LoadedPanelName;

	TArray<FName> WaitShowPanelName;

	//����ͼƬ
	UPROPERTY()
		UImage* MaskPanel;

	//͸����ֵ
	FLinearColor NormalLucency;
	FLinearColor TranslucenceLucency;
	FLinearColor ImPenetrableLucency;

	//����ѭ���������������ʾ��������ʱѭ����������
	FName WaitShowTaskName;

private:
	//���ջص���UI���
	void AcceptUIPanel(FName PanelName, UUserWidget* PanelWidget);

private:
	FTimerHandle WaitShowHandle;
};
