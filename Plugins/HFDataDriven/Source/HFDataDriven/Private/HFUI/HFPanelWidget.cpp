// Fill out your copyright notice in the Description page of Project Settings.


#include "HFUI/HFPanelWidget.h"
#include "TimerManager.h"

void UHFPanelWidget::PanelEnter()
{
	//HFH::Debug() << "PanelEnter..." << HFH::Endl();
	SetVisibility(ESlateVisibility::Visible);
	DisplayEnterMovie();
}

void UHFPanelWidget::PanelDisplay()
{
	SetVisibility(ESlateVisibility::Visible);
	DisplayEnterMovie();
}

void UHFPanelWidget::PanelHidden()
{
	GetHFWorld()->GetTimerManager().SetTimer(HideHandle, this, &UHFPanelWidget::SetSelfHidden, 1.0f,
		false, DisplayLeaveMovie());
	//SetVisibility(ESlateVisibility::Hidden);
}

void UHFPanelWidget::PanelFreeze()
{

}

void UHFPanelWidget::PanelResume()
{

}

void UHFPanelWidget::PanelExit()
{

}

void UHFPanelWidget::SetSelfHidden()
{
	SetVisibility(ESlateVisibility::Hidden);
	GetHFWorld()->GetTimerManager().ClearTimer(HideHandle);
}
