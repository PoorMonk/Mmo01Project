// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HFMMInterface.h"
#include "HFMessage.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFMessage : public UObject, public IHFMMInterface
{
	GENERATED_BODY()
	
public:
	UHFMessage();

	virtual void MessageInit();
	virtual void MessageBeginPlay();
	virtual void MessageTick(float DeltaSeconds);

	//注册调用接口
	template<typename RetType, typename... VarTypes>
	HFCallHandle<RetType, VarTypes...> RegisterCallPort(FName CallName);

	//注册方法接口
	template<typename RetType, typename... VarTypes>
	HFFuncHandle RegisterFuncPort(FName CallName, TFunction<RetType(VarTypes...)> InsFunc);

protected:
	//事件队列
	HFMsgQueue* MsgQueue;
};

template<typename RetType, typename... VarTypes>
HFCallHandle<RetType, VarTypes...>
UHFMessage::RegisterCallPort(FName CallName)
{
	return MsgQueue->RegisterCallPort<RetType, VarTypes...>(CallName);
}

template<typename RetType, typename... VarTypes>
HFFuncHandle UHFMessage::RegisterFuncPort(FName CallName, TFunction<RetType(VarTypes...)> InsFunc)
{
	return MsgQueue->RegisterFuncPort<RetType, VarTypes...>(CallName, InsFunc);
}
