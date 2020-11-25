// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/HFCommon/HFTypes.h"

TSharedPtr<HFRecord> HFRecord::Get()
{
	if (!RecordInst.IsValid())
	{
		RecordInst = MakeShareable(new HFRecord());
	}

	return RecordInst;
}

TSharedPtr<HFRecord> HFRecord::RecordInst = nullptr;
