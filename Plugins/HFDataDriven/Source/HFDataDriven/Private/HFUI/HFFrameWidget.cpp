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

	//生成遮罩
	MaskPanel = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());

	//设置透明度
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
	//如果面板已显示
	if (ShowPanelGroup.Contains(PanelName) || PopPanelStack.Contains(PanelName))
	{
		return;
	}

	//判断是否已经加载该面板
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

	//如果存在该面板
	if (AllPanelGroup.Contains(PanelName))
	{
		//判断是否是第一次显示在界面上
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
			//判断最底层的布局控件是否是Canvas
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

		//如果存在布局控件, 试图把最后一个布局控件转换成Overlay
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
			//添加布局控件到界面最顶层
			UCanvasPanelSlot* FrameCanvasSlot = RootCanvas->AddChildToCanvas(WorkLayout);
			FrameCanvasSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			FrameCanvasSlot->SetOffsets(FMargin(0.f, 0.f, 0.f, 0.f));
			//添加到激活画布组
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
	//添加UI面板到父控件
	UCanvasPanelSlot* PanelSlot = WorkLayout->AddChildToCanvas(PanelWidget);
	PanelSlot->SetAnchors(PanelWidget->UINature.Anchors);
	PanelSlot->SetOffsets(PanelWidget->UINature.Offsets);

	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void UHFFrameWidget::EnterPanelDoNothing(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget)
{
	//添加UI面板到Overlay
	UOverlaySlot* PanelSlot = WorkLayout->AddChildToOverlay(PanelWidget);
	PanelSlot->SetPadding(PanelWidget->UINature.Offsets);
	PanelSlot->SetHorizontalAlignment(PanelWidget->UINature.HAlign);
	PanelSlot->SetVerticalAlignment(PanelWidget->UINature.VAlign);

	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	PanelWidget->PanelEnter();
}

void UHFFrameWidget::EnterPanelHideOther(UCanvasPanel* WorkLayout, UHFPanelWidget* PanelWidget)
{
	//将显示组的同一层级的其他对象都隐藏, 如果是Level_All就全部隐藏, Level_All优先级高
	for (TMap<FName, UHFPanelWidget*>::TIterator It(ShowPanelGroup); It; ++It)
		if (PanelWidget->UINature.LayoutLevel == ELayoutLevel::Level_All || PanelWidget->UINature.LayoutLevel == It.Value()->UINature.LayoutLevel)
			It.Value()->PanelHidden();

	//添加UI面板到Layout
	UCanvasPanelSlot* PanelSlot = WorkLayout->AddChildToCanvas(PanelWidget);
	PanelSlot->SetAnchors(PanelWidget->UINature.Anchors);
	PanelSlot->SetOffsets(PanelWidget->UINature.Offsets);

	//添加UI面板添加到显示组
	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	//调用进入界面生命周期函数
	PanelWidget->PanelEnter();
}

void UHFFrameWidget::EnterPanelHideOther(UOverlay* WorkLayout, UHFPanelWidget* PanelWidget)
{
	//将显示组的同一层级的其他对象都隐藏, 如果是Level_All就全部隐藏, Level_All优先级高
	for (TMap<FName, UHFPanelWidget*>::TIterator It(ShowPanelGroup); It; ++It)
		if (PanelWidget->UINature.LayoutLevel == ELayoutLevel::Level_All || PanelWidget->UINature.LayoutLevel == It.Value()->UINature.LayoutLevel)
			It.Value()->PanelHidden();

	//添加到UOverlay
	UOverlaySlot* PanelSlot = WorkLayout->AddChildToOverlay(PanelWidget);
	PanelSlot->SetPadding(PanelWidget->UINature.Offsets);
	PanelSlot->SetHorizontalAlignment(PanelWidget->UINature.HAlign);
	PanelSlot->SetVerticalAlignment(PanelWidget->UINature.VAlign);

	//添加UI面板添加到显示组
	ShowPanelGroup.Add(PanelWidget->GetObjectName(), PanelWidget);
	//调用进入界面生命周期函数
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
	//获取遮罩当前父控件
	UPanelWidget* MaskParent = MaskPanel->GetParent();
	if (MaskParent)
	{
		//比较当前父控件与将要插入的父控件是否相同, 当前父控件的子控件为1
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
		//将遮罩从父级移除
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

	//注册到框架，不注册类名
	PanelWidget->RegisterToModule(ModuleIndex, BackcallName);
	AllPanelGroup.Add(BackcallName, PanelWidget);
}
