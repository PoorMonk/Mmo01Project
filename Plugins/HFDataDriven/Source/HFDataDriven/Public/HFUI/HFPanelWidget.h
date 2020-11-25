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
	//UI�����������
	virtual void PanelEnter();		//��һ�ν�����棬ֻ��ִ��һ��
	virtual void PanelDisplay();	//��ʾ�Ѵ��ڽ���
	virtual void PanelHidden();		//����
	virtual void PanelFreeze();		//����
	virtual void PanelResume();		//�ָ�
	virtual void PanelExit();		//����

	//�����ص�����
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
