// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleItemWidget.h"
#include "Image.h"
#include "HFCommon.h"

void URoleItemWidget::InitWidget(FString name, UTexture2D* texture)
{
	RoleName = name;
	Img_Role->SetBrushFromTexture(texture);
}

void URoleItemWidget::ShowMask(bool bShow)
{
	if (bShow)
	{
		Img_Mask->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Img_Mask->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URoleItemWidget::OnBtnDownEvent()
{
	//HFH::Debug() << "RoleName: " << RoleName << HFH::Endl();
	RoleClickedDele.ExecuteIfBound(RoleName);
}
