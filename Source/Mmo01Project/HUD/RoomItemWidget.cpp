// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomItemWidget.h"
#include "Overlay.h"

void URoomItemWidget::ShowUI(uint32 type)
{
	switch (type)
	{
	case 0:
		Overlay_Room1->SetVisibility(ESlateVisibility::Hidden);
		Overlay_Room2->SetVisibility(ESlateVisibility::Visible);
		break;
	case 1:
		Overlay_Room1->SetVisibility(ESlateVisibility::Visible);
		Overlay_Room2->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
}
