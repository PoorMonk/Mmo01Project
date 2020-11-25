// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/HFObject/HFUserWidget.h"

void UHFUserWidget::HFRelease()
{
	IHFOOInterface::HFRelease();

	RemoveFromParent();
	RemoveFromRoot();
	ConditionalBeginDestroy();
}
