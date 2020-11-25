// Fill out your copyright notice in the Description page of Project Settings.


#include "HFUI/HFFrameWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "HFUI/HFPanelWidget.h"
#include "Engine/GameEngine.h"
#include "TimerManager.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

bool UHFFrameWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	RootCanvas = Cast<UCanvasPanel>(GetRootWidget());
	RootCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	//��������
	MaskPanel = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());

	//����͸����
	NormalLucency = FLinearColor(1.f, 1.f, 1.f, 0.f);
	TranslucenceLucency = FLinearColor(0.f, 0.f, 0.f, 0.6f);
	ImPenetrableLucency = FLinearColor(0.f, 0.f, 0.f, 0.3f);

	WaitShowTaskName = FName("WaitShowTask");

	return true;
}

void UHFFrameWidget::AdvanceLoadPanel(FName PanelName)
{
	if (AllPanelGroup.Contains(PanelName) || LoadedPanelName.Contains(PanelName))
	{
		return;
	}

	BuildSingleClassWealth(EWealthType::Widget, PanelName, "AcceptedAdvancePanel");
	LoadedPanelName.Push(PanelName);
}

void UHFFrameWidget::ShowUIPanel(FName PanelName)
{
	//����������ʾ
	if (ShowPanelGroup.Contains(PanelName) || PopPanelStack.Contains(PanelName))
	{
		return;
	}

	//�ж��Ƿ��Ѿ����ظ����
	if (!AllPanelGroup.Contains(PanelName) && !LoadedPanelName.Contains(PanelName))
	{
		BuildSingleClassWealth(EWealthType::Widget, PanelName, "AccepPanelWidget");
		LoadedPanelName.Push(PanelName);
		return;
	}

	if (!AllPanelGroup.Contains(PanelName) && LoadedPanelName.Contains(PanelName))
	{
		WaitShowPanelName.Push(PanelName);
		GetHFWorld()->GetTimerManager().SetTimer(WaitShowHandle, this, &UHFFrameWidget::WaitShowPanel, 0.3f, true, 0.3f);
		return;
	}

	//������ڸ����
	if (AllPanelGroup.Contains(PanelName))
	{
		//�ж��Ƿ��ǵ�һ����ʾ�ڽ�����
		UHFPanelWidget* PanelWidget = *AllPanelGroup.Find(PanelName);
		if (PanelWidget->GetParent())
		{
			DoShowUIPanel(PanelName);
		}
		else
		{
			DoEnterUIPanel(PanelName);
		}
	}
}

void UHFFrameWidget::HideUIPanel(FName PanelName)
{

}

void UHFFrameWidget::ExitUIPanel(FName PanelName)
{

}

void UHFFrameWidget::AcceptedAdvancePanel(FName BackcallName, UUserWidget* BackcallWidget)
{
	AcceptUIPanel(BackcallName, BackcallWidget);
}

void UHFFrameWidget::AccepPanelWidget(FName BackcallName, UUserWidget* BackcallWidget)
{
	AcceptUIPanel(BackcallName, BackcallWidget);
	DoEnterUIPanel(BackcallName);
}

void UHFFrameWidget::ExitCallBack(ELayoutType LayoutType, UPanelWidget* InLayout)
{

}

void UHFFrameWidget::DoEnterUIPanel(FName PanelName)
{
	UHFPanelWidget* PanelWidget = *AllPanelGroup.Find(PanelName);
	if (PanelWidget->UINature.LayoutType == ELayoutType::Canvas)
	{
		UCanvasPanel* WorkLayout = nullptr;
		if (RootCanvas->GetChildrenCount() > 0)
		{
			//�ж���ײ�Ĳ��ֿؼ��Ƿ���Canvas
			WorkLayout = Cast<UCanvasPanel>(RootCanvas->GetChildAt(RootCanvas->GetChildrenCount() - 1));
			if (!WorkLayout)
			{
				if (!UnActiveCanvas.Num())
				{
					WorkLayout = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
					WorkLayout->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
					FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
					FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
				}
				else
				{
					WorkLayout = UnActiveCanvas.Pop();
				}
				ActiveCanvas.Push(WorkLayout);
			}
		}
		else
		{
			if (!UnActiveCanvas.Num())
			{
				WorkLayout = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
				WorkLayout->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
				FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
				FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			}
			else
			{
				WorkLayout = UnActiveCanvas.Pop();
			}
			ActiveCanvas.Push(WorkLayout);
		}

		switch (PanelWidget->UINature.PanelShowType)
		{
		case EPanelShowType::DoNothing:
			EnterPanelDoNothing(WorkLayout, PanelWidget);
			break;
		case EPanelShowType::HideOther:
			EnterPanelHideOther(WorkLayout, PanelWidget);
			break;
		case EPanelShowType::Reverse:
			EnterPanelReverse(WorkLayout, PanelWidget);
			break;
		}
	}
	else
	{
		UOverlay* WorkLayout = NULL;

		//������ڲ��ֿؼ�, ��ͼ�����һ�����ֿؼ�ת����Overlay
		if (RootCanvas->GetChildrenCount() > 0)
			WorkLayout = Cast<UOverlay>(RootCanvas->GetChildAt(RootCanvas->GetChildrenCount() - 1));

		if (!WorkLayout)
		{
			if (UnActiveOverlay.Num() == 0)
			{
				WorkLayout = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
				WorkLayout->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
				WorkLayout = UnActiveOverlay.Pop();
			//��Ӳ��ֿؼ����������
			UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
			FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			//��ӵ��������
			ActiveOverlay.Push(WorkLayout);
		}

		switch (PanelWidget->UINature.PanelShowType)
		{
		case EPanelShowType::DoNothing:
			EnterPanelDoNothing(WorkLayout, PanelWidget);
			break;
		case EPanelShowType::HideOther:
			EnterPanelHideOther(WorkLayout, PanelWidget);
			break;
		case EPanelShowType::Reverse:
			EnterPanelReverse(WorkLayout, PanelWidget);
			break;
		}
	}
}

void UHFFrameWidget::DoShowUIPanel(FName PanelName)
{

}

void UHFFrameWidget::WaitShowPanel()
{
	TArray<FName> CompleteName;
	for (int i = 0; i < WaitShowPanelName.Num(); ++i)
	{
		if (AllPanelGroup.Contains(WaitShowPanelName[i]))
		{
			DoEnterUIPanel(WaitShowPanelName[i]);
			CompleteName.Push(WaitShowPanelName[i]);
		}
	}
	for (int i = 0; i < CompleteName.Num(); ++i)
	{
		WaitShowPanelName.Remove(CompleteName[i]);
	}
	if (!WaitShowPanelName.Num())
	{
		GetHFWorld()->GetTimerManager().ClearTimer(WaitShowHandle);
	}
}

void UHFFrameWidget::EnterPanelDoNothing(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget)
{
	//���UI��嵽���ؼ�
	UCanvasPanelSlot* PanelSlot = WorkLayout->AddChildToCanvas(PanelWidget);
	PanelSlot->SetAnchors(PanelWidget->UINature.Anchors);
	PanelSlot->SetOffsets(PanelWidget->UINature.Offsets);

	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void UHFFrameWidget::EnterPanelDoNothing(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget)
{
	//���UI��嵽Overlay
	UOverlaySlot* PanelSlot = WorkLayout->AddChildToOverlay(PanelWidget);
	PanelSlot->SetPadding(PanelWidget->UINature.Offsets);
	PanelSlot->SetHorizontalAlignment(PanelWidget->UINature.HAlign);
	PanelSlot->SetVerticalAlignment(PanelWidget->UINature.VAlign);

	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void UHFFrameWidget::EnterPanelHideOther(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget)
{
	//����ʾ���ͬһ�㼶��������������, �����Level_All��ȫ������, Level_All���ȼ���
	for (TMap<FName, UHFPanelWidget*>::TIterator It(ShowPanelGroup); It; ++It)
		if (PanelWidget->UINature.LayoutLevel == ELayoutLevel::Level_All || PanelWidget->UINature.LayoutLevel == It.Value()->UINature.LayoutLevel)
			It.Value()->PanelHidden();

	//���UI��嵽Layout
	UCanvasPanelSlot* PanelSlot = WorkLayout->AddChildToCanvas(PanelWidget);
	PanelSlot->SetAnchors(PanelWidget->UINature.Anchors);
	PanelSlot->SetOffsets(PanelWidget->UINature.Offsets);

	//���UI�����ӵ���ʾ��
	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	//���ý�������������ں���
	PanelWidget->PanelEnter();
}

void UHFFrameWidget::EnterPanelHideOther(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget)
{
	//����ʾ���ͬһ�㼶��������������, �����Level_All��ȫ������, Level_All���ȼ���
	for (TMap<FName, UHFPanelWidget*>::TIterator It(ShowPanelGroup); It; ++It)
		if (PanelWidget->UINature.LayoutLevel == ELayoutLevel::Level_All || PanelWidget->UINature.LayoutLevel == It.Value()->UINature.LayoutLevel)
			It.Value()->PanelHidden();

	//��ӵ�UOverlay
	UOverlaySlot* PanelSlot = WorkLayout->AddChildToOverlay(PanelWidget);
	PanelSlot->SetPadding(PanelWidget->UINature.Offsets);
	PanelSlot->SetHorizontalAlignment(PanelWidget->UINature.HAlign);
	PanelSlot->SetVerticalAlignment(PanelWidget->UINature.VAlign);

	//���UI�����ӵ���ʾ��
	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	//���ý�������������ں���
	PanelWidget->PanelEnter();
}

void UHFFrameWidget::EnterPanelReverse(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget)
{

}

void UHFFrameWidget::EnterPanelReverse(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget)
{

}

void UHFFrameWidget::ActiveMask(UCanvasPanel* WorkLayout, EPanelLucenyType LucenyType)
{

}

void UHFFrameWidget::ActiveMask(UOverlay* WorkLayout, EPanelLucenyType LucenyType)
{

}

void UHFFrameWidget::RemoveMaskPanel(UPanelWidget* WorkLayout /*= nullptr*/)
{
	//��ȡ���ֵ�ǰ���ؼ�
	UPanelWidget* MaskParent = MaskPanel->GetParent();
	if (MaskParent)
	{
		//�Ƚϵ�ǰ���ؼ��뽫Ҫ����ĸ��ؼ��Ƿ���ͬ, ��ǰ���ؼ����ӿؼ�Ϊ1
		if (MaskParent != WorkLayout && MaskParent->GetChildrenCount() == 1)
		{
			MaskParent->RemoveFromParent();
			UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(MaskParent);
			UOverlay* ParentOverlay = Cast<UOverlay>(MaskParent);
			if (ParentCanvas)
			{
				ActiveCanvas.Remove(ParentCanvas);
				UnActiveCanvas.Push(ParentCanvas);
			}
			else if (ParentOverlay)
			{
				ActiveOverlay.Remove(ParentOverlay);
				UnActiveOverlay.Push(ParentOverlay);
			}
		}
		//�����ִӸ����Ƴ�
		MaskPanel->RemoveFromParent();
	}
}

void UHFFrameWidget::AcceptUIPanel(FName BackcallName, UUserWidget* BackcallWidget)
{
	UHFPanelWidget* PanelWidget = Cast<UHFPanelWidget>(BackcallWidget);
	if (!PanelWidget)
	{
		HFH::Debug() << "Load UI Panel: " << BackcallName << "is not HFWidget" << HFH::Endl();
		return;
	}

	//ע�ᵽ��ܣ���ע������
	PanelWidget->RegisterToModule(ModuleIndex, BackcallName);
	AllPanelGroup.Add(BackcallName, PanelWidget);
}
