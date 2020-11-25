// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/GameEngine.h"
#include "Widgets/Layout/Anchors.h"
#include "Engine/DataAsset.h"
#include "HFTypes.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFTypes : public UObject
{
	GENERATED_BODY()
	
};

//框架自定义Debug输出类
#pragma region LogDebug
class HFDATADRIVEN_API HFRecord
{
public:
	inline HFRecord() { }
	~HFRecord() { }

	static TSharedPtr<HFRecord> Get();

	//设置参数
	inline void InitParam(float time, FColor color)
	{
		ShowTime = time;
		ShowColor = color;
	}

	//执行打印方法
	inline void Output()
	{
		switch (PatternID)
		{
		case 0:
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, ShowTime, ShowColor, RecordInfo);
			}
			break;
		case 1:
			UE_LOG(LogTemp, Log, TEXT("%s"), *RecordInfo);
			break;
		case 2:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *RecordInfo);
			break;
		case 3:
			UE_LOG(LogTemp, Error, TEXT("%s"), *RecordInfo);
			break;
		default:
			break;
		}
		RecordInfo.Empty();
	}

	//重写操作符
	inline HFRecord& operator<<(FString Info){ RecordInfo.Append(Info); return *this; }
	inline HFRecord& operator<<(FName Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(FText Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(const char* Info) { RecordInfo += Info; return *this; }
	inline HFRecord& operator<<(const char Info) { RecordInfo.AppendChar(Info); return *this; }
	inline HFRecord& operator<<(int32 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline HFRecord& operator<<(uint64 Info) { RecordInfo.Append(FString::FromInt(Info)); return *this; }
	inline HFRecord& operator<<(float Info) { RecordInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline HFRecord& operator<<(double Info) { RecordInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline HFRecord& operator<<(bool Info) { RecordInfo.Append(Info ? FString("true") : FString("false")); return *this; }
	inline HFRecord& operator<<(FVector2D Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(FVector Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(FRotator Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(FQuat Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(FTransform Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(FMatrix Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(FColor Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline HFRecord& operator<<(FLinearColor Info) { RecordInfo.Append(Info.ToString()); return *this; }
	inline void operator<<(HFRecord& Record)
	{
		Record.Output();
	}

	//输出样例(最后以自身为参数来执行真正的输出函数)
	//HFRecord::Get() << FString("haha") << FName("Harkey") << int << float << HFRecord::Get();

public:
	//打印模式，0：debug，1：log，2：Warning，3：Error
	uint8 PatternID;

private:
	//单例对象
	static TSharedPtr<HFRecord> RecordInst;

	//生成的字符串
	FString RecordInfo;
	//显示时间
	float ShowTime;
	//显示颜色
	FColor ShowColor;
};
#pragma endregion

#pragma region LifeTimePart
//生命周期
UENUM()
enum class EBaseObjectLife : uint8
{
	None = 0,
	Init,
	Loading,
	Register,
	Enable,
	Disable,
	UnRegister,
	UnLoading
};

//对象状态
UENUM()
enum class EBaseObjectState : uint8
{
	Active = 0,		//激活状态
	Stable,			//稳定状态
	Destroy			//销毁状态
};
#pragma endregion

#pragma region ReflectPart
//对象调用协议
UENUM()
enum class EAgreementType : uint8
{
	SelfObject,			//跟传入的对象通信
	OtherObject,		//跟传入的对象之外的对象通信
	ClassOtherObject,	//跟传入的对象的相同类的其它对象通信
	SelfClass,			//跟这个类的对象通信
	OtherClass,			//跟其它类通信
	All					//跟所有的对象通信
};

//调用结果
UENUM()
enum class ECallResult : uint8
{
	NoModule = 0,	//缺失模组
	LackObject,		//缺失部分对象
	NoFunction,		//缺失方法
	Succeed			//调用成功
};

//通信参数结构体基类
struct HFParam
{
public:
	//调用结果
	ECallResult CallResult;

	//参数指针
	void* ParamPtr;
};

//通信协议，Module方法
struct  HFModuleAgreement
{
public:
	//模组ID
	int32 ModuleIndex;

	//方法名
	FName FunctionName;
};

//通信协议， HFOOInterface方法
struct HFObjectAgreement
{
public:
	//模组ID
	int32 ModuleIndex;

	//协议类型
	EAgreementType AgreementType;

	//对象组名
	TArray<FName> ObjectGroup;

	//方法名
	FName FunctionName;
};

#pragma endregion

#pragma region HFAnyFunc
//存储任意类型的函数
struct HFAnyFunc 
{
	struct BaseFunc
	{
	public:
		virtual ~BaseFunc() { }
	};
	template<typename RetType, typename... VarTypes>
	struct ValFunc : public BaseFunc
	{
	public:
		TFunction<RetType(VarTypes...)> TarFunc;
		ValFunc(const TFunction<RetType(VarTypes...)> InsFunc) : TarFunc(InsFunc) { }
		RetType Execute(VarTypes... Params)
		{
			return TarFunc(Params...);
		}
	};
	BaseFunc* FuncPtr;
public:
	HFAnyFunc() : FuncPtr(nullptr) { }
	template<typename RetType, typename... VarTypes>
	HFAnyFunc(const TFunction<RetType(VarTypes...)> InsFunc) : FuncPtr(new ValFunc<RetType, VarTypes...>(InsFunc)) { }
	~HFAnyFunc() { if (FuncPtr) delete FuncPtr; }
	template<typename RetType, typename... VarTypes>
	RetType Execute(VarTypes... Params)
	{
		ValFunc<RetType, VarTypes...>* SubFuncPtr = static_cast<ValFunc<RetType, VarTypes...>*>(FuncPtr);
		return SubFuncPtr->Execute(Params...);
	}
	template<typename RetType, typename... VarTypes>
	TFunction<RetType(VarTypes...)>& GetFunc()
	{
		ValFunc<RetType, VarTypes...>* SubFuncPtr = static_cast<ValFunc<RetType, VarTypes...>*>(FuncPtr);
		return SubFuncPtr->TarFunc;
	}
};
#pragma endregion

#pragma region AnyElement
//存储任意类型的数据结构
struct AnyElement
{
	//元素父结构体
	struct BaseElement
	{
	public:
		virtual ~BaseElement() { }
	};
	//实际存储值得结构体
	template<typename T>
	struct ValueElement : public BaseElement
	{
	public:
		T Value;
		ValueElement(const T& InValue) : Value(InValue) { }
	};
	//父结构体指针，用于存储实例化得子结构体的地址
	BaseElement* ElementPtr;

public:
	AnyElement() : ElementPtr(nullptr) { }
	//构造函数传入值并且实例化子结构体存储于父结构体指针
	template<typename T>
	AnyElement(const T& InValue) : ElementPtr(new ValueElement<T>(InValue)) { }
	~AnyElement() { if (ElementPtr) delete ElementPtr; }
	//获取保存的变量
	template<typename T>
	T& Get()
	{
		ValueElement<T>* SubPtr = static_cast<ValueElement<T>*>(ElementPtr);
		return SubPtr->Value;
	}
};
#pragma endregion

#pragma region MsgNode
//事件节点
struct HFMsgNode
{
	//被调用的接口数量
	int32 CallCount;
	//方法列表
	TMap<int32, HFAnyFunc*> FuncQueue;
	//注册方法
	template<typename RetType, typename... VarTypes>
	int32 RegisterFunc(TFunction<RetType(VarTypes...)> InsFunc);
	//注销方法
	void UnRegisterFunc(int32 FuncID)
	{
		//从列表移除对象
		HFAnyFunc* DesPtr = *FuncQueue.Find(FuncID);
		FuncQueue.Remove(FuncID);
		delete DesPtr;
	}
	//清空节点
	void ClearNode()
	{
		for (TMap<int32, HFAnyFunc*>::TIterator It(FuncQueue); It; ++It)
		{
			delete It.Value();
		}
	}
	//执行方法
	template<typename RetType, typename... VarTypes>
	RetType Execute(VarTypes... Params);
	//判断是否有绑定函数
	bool IsBound() { return FuncQueue.Num() > 0; }
	//执行绑定方法
	template<typename RetType, typename... VarTypes>
	bool ExecuteIfBound(VarTypes... Params);

	HFMsgNode() : CallCount(0) { }
};

template<typename RetType, typename... VarTypes>
int32 HFMsgNode::RegisterFunc(TFunction<RetType(VarTypes...)> InsFunc)
{
	//获取方法序列里的所有下标
	TArray<int32> FuncKeyQuene;
	FuncQueue.GenerateKeyArray(FuncKeyQuene);
	//获取新下标
	int32 NewID;
	for (int32 i = FuncKeyQuene.Num(); i >= 0; --i)
	{
		if (!FuncKeyQuene.Contains(i))
		{
			NewID = i;
			break;
		}
	}
	//将新方法添加到节点
	FuncQueue.Add(NewID, new HFAnyFunc(InsFunc));
	return NewID;
}

template<typename RetType, typename... VarTypes>
RetType HFMsgNode::Execute(VarTypes... Params)
{
	//遍历第二个到最后一个
	TMap<int32, HFAnyFunc*>::TIterator It(FuncQueue);
	++It;
	for (; It; ++It)
	{
		It.Value()->Execute<RetType, VarTypes...>(Params...);
	}
	//获取第一个方法
	TMap<int32, HFAnyFunc*>::TIterator IBegin(FuncQueue);
	return IBegin.Value()->Execute<RetType, VarTypes...>(Params...);
}

template<typename RetType, typename... VarTypes>
bool HFMsgNode::ExecuteIfBound(VarTypes... Params)
{
	if (!IsBound()) return false;

	for (TMap<int32, HFAnyFunc*>::TIterator It(FuncQueue); It; ++It)
	{
		It.Value()->Execute<RetType, VarTypes...>(Params...);
	}
	return true;
}

#pragma endregion

#pragma region HFCallHandle
struct HFMsgQueue;

template<typename RetType, typename... VarTypes>
struct HFCallHandle
{
	//事件队列
	HFMsgQueue* MsgQueue;
	//节点名，调用名
	FName CallName;
	//是否有效,用于重写等于操作符保存状态
	TSharedPtr<bool> IsActived;
	//执行方法
	RetType Execute(VarTypes... Params);
	//是否已经绑定
	bool IsBound();
	//执行绑定函数
	bool ExecuteIfBound(VarTypes... Params);
	//注销调用接口
	void UnRegister();

	HFCallHandle() { }

	HFCallHandle(HFMsgQueue* MQ, FName CN)
	{
		MsgQueue = MQ;
		CallName = CN;
		IsActived = MakeShareable<bool>(new bool(true));
	}

	//重写操作符
	HFCallHandle<RetType, VarTypes...>& operator=(const HFCallHandle<RetType, VarTypes...>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		MsgQueue = other.MsgQueue;
		CallName = other.CallName;
		IsActived = other.IsActived;
		return *this;
	}
};

template<typename RetType, typename... VarTypes>
void HFCallHandle<RetType, VarTypes...>::UnRegister()
{
	if (*IsActived.Get())
	{
		MsgQueue->UnRegisterCallPort(CallName);
	}
	*IsActived.Get() = false;
}

template<typename RetType, typename... VarTypes>
bool HFCallHandle<RetType, VarTypes...>::ExecuteIfBound(VarTypes... Params)
{
	if (!IsBound() || !(*IsActived.Get()))
	{
		return false;
	}
	MsgQueue->Execute<RetType, VarTypes...>(CallName, Params...);
	return true;
}

template<typename RetType, typename... VarTypes>
bool HFCallHandle<RetType, VarTypes...>::IsBound()
{
	if (!(*IsActived.Get()))
	{
		return false;
	}
	return MsgQueue->IsBound(CallName);
}

template<typename RetType, typename... VarTypes>
RetType HFCallHandle<RetType, VarTypes...>::Execute(VarTypes... Params)
{
	if (!IsBound() || !(*IsActived.Get()))
	{
		return NULL;
	}
	return MsgQueue->Execute<RetType, VarTypes...>(CallName, Params...);
}

#pragma endregion

#pragma region HFMsgQueue
struct HFFuncHandle;

struct HFMsgQueue
{
	//节点序列
	TMap<FName, HFMsgNode> MsgQueue;
	//注册调用接口
	template<typename RetType, typename... VarTypes>
	HFCallHandle<RetType, VarTypes...> RegisterCallPort(FName CallName);
	//注册方法接口
	template<typename RetType, typename... VarTypes>
	HFFuncHandle RegisterFuncPort(FName CallName, TFunction<RetType(VarTypes...)> InsFunc);
	//移除调用接口
	void UnRegisterCallPort(FName CallName)
	{
		if (!MsgQueue.Contains(CallName))
		{
			return;
		}
		HFMsgNode* MsgNode = MsgQueue.Find(CallName);
		MsgNode->CallCount--;
		if (MsgNode->CallCount <= 0)
		{
			MsgNode->ClearNode();
			MsgQueue.Remove(CallName);
		}
	}
	//注销方法接口
	void UnRegisterFuncPort(FName CallName, int32 FuncID)
	{
		if (!MsgQueue.Contains(CallName))
		{
			return;
		}
		MsgQueue.Find(CallName)->UnRegisterFunc(FuncID);
	}
	//执行方法接口
	template<typename RetType, typename... VarTypes>
	RetType Execute(FName CallName, VarTypes... Params);
	//是否已经绑定方法
	bool IsBound(FName CallName) { return MsgQueue.Find(CallName)->IsBound(); }
};

template<typename RetType, typename... VarTypes>
HFCallHandle<RetType, VarTypes...>
HFMsgQueue::RegisterCallPort(FName CallName)
{
	//如果已经存在对应CallName的调用接口，就把计数器+1
	if (MsgQueue.Contains(CallName))
	{
		MsgQueue.Find(CallName)->CallCount++;
	}
	else
	{
		//创建新的事件节点并添加到队列
		MsgQueue.Add(CallName, HFMsgNode());
		//计数器加1
		MsgQueue.Find(CallName)->CallCount++;
	}
	//返回调用句柄
	return HFCallHandle<RetType, VarTypes...>(this, CallName);
}

template<typename RetType, typename... VarTypes>
HFFuncHandle HFMsgQueue::RegisterFuncPort(FName CallName, TFunction<RetType(VarTypes...)> InsFunc)
{
	//获取新的方法下标
	int32 FuncID;
	if (!MsgQueue.Contains(CallName))
	{
		MsgQueue.Add(CallName, HFMsgNode());
	}
	FuncID = MsgQueue.Find(CallName)->RegisterFunc(InsFunc);
	return HFFuncHandle(this, CallName, FuncID);
}

template<typename RetType, typename... VarTypes>
RetType HFMsgQueue::Execute(FName CallName, VarTypes... Params)
{
	return MsgQueue.Find(CallName)->Execute<RetType, VarTypes...>(Params...);
}

#pragma endregion

#pragma region HFFuncHandle

struct HFFuncHandle
{
	//消息队列
	HFMsgQueue* MsgQueue;
	//调用名字
	FName CallName;
	//方法ID
	int32 FuncID;
	//是否有效
	TSharedPtr<bool> IsActived;
	//注销方法
	void UnRegister()
	{
		if (*IsActived.Get())
		{
			MsgQueue->UnRegisterFuncPort(CallName, FuncID);
		}
		*IsActived.Get() = false;
	}

	HFFuncHandle() { }

	HFFuncHandle(HFMsgQueue* MQ, FName CN, int32 FI)
	{
		MsgQueue = MQ;
		CallName = CN;
		FuncID = FI;
		IsActived = MakeShareable<bool>(new bool(true));
	}

	HFFuncHandle& operator=(const HFFuncHandle& other)
	{
		if (this == &other)
		{
			return *this;
		}
		MsgQueue = other.MsgQueue;
		CallName = other.CallName;
		FuncID = other.FuncID;
		IsActived = other.IsActived;
		return *this;
	}

};
#pragma endregion

#pragma region Wealth

USTRUCT()
struct FWealthItem
{
	GENERATED_BODY()

public:
	//对象名
	UPROPERTY(EditAnywhere)
		FName ObjectName;
	//类名
	UPROPERTY(EditAnywhere)
		FName ClassName;
};

USTRUCT()
struct FWealthObject : public FWealthItem 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UObject> WealthClass;
};

USTRUCT()
struct FWealthActor : public FWealthItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> WealthClass;

	UPROPERTY(EditAnywhere)
		FTransform Transform;
};

USTRUCT()
struct FWealthWidget : public FWealthItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WealthClass;
};

//Object资源结构体
USTRUCT()
struct FObjectWealthEntry 
{
	GENERATED_BODY()

public:
	//资源名
	UPROPERTY(EditAnywhere)
		FName WealthName;
	//资源种类名
	UPROPERTY(EditAnywhere)
		FName WealthKind;
	//资源链接
	UPROPERTY(EditAnywhere)
		FStringAssetReference WealthPath;
	//加载出来的对象
	UPROPERTY()
		UObject* WealthObj;
};

//UClass类型枚举
UENUM()
enum class EWealthType : uint8
{
	Object,
	Actor,
	Widget
};

//Class资源结构体
USTRUCT()
struct FClassWealthEntry 
{
	GENERATED_BODY()

public:
	//资源名
	UPROPERTY(EditAnywhere)
		FName WealthName;
	//资源种类名
	UPROPERTY(EditAnywhere)
		FName WealthKind;
	//资源类别
	UPROPERTY(EditAnywhere)
		EWealthType WealthType;
	//资源链接
	UPROPERTY(EditAnywhere)
		TSoftClassPtr<UObject> WealthPtr;
	//加载出来的对象
	UPROPERTY()
		UClass* WealthClass;
};

//纯获取链接结构体，不进行同异步加载
USTRUCT()
struct FWealthURL 
{
	GENERATED_BODY()

public:
	//资源名
	UPROPERTY(EditAnywhere)
		FName WealthName;

	//资源种类名
	UPROPERTY(EditAnywhere)
		FName WealthKind;

	//资源链接
	UPROPERTY(EditAnywhere)
		TSoftClassPtr<UObject> WealthPtr;

	UPROPERTY(EditAnywhere)
		FStringAssetReference WealthPath;
};

UCLASS()
class HFDATADRIVEN_API UWealthData : public UDataAsset
{
	GENERATED_BODY()

public:
	//模组名字，默认注册到ModuleName对应的模组，如果为空表示使用于多个模组下
	UPROPERTY(EditAnywhere)
		FName ModuleName;

	//自动生成的对象
	UPROPERTY(EditAnywhere)
		TArray<FWealthObject> AutoObjectData;

	//自动生成的Actor
	UPROPERTY(EditAnywhere)
		TArray<FWealthActor> AutoActorData;

	//自动生成的Widget
	UPROPERTY(EditAnywhere)
		TArray<FWealthWidget> AutoWidgetData;

	//Object资源链接集合
	UPROPERTY(EditAnywhere)
		TArray<FObjectWealthEntry> ObjectWealthData;

	//Class资源链接集合
	UPROPERTY(EditAnywhere)
		TArray<FClassWealthEntry> ClassWealthData;

	//资源链接集合
	UPROPERTY(EditAnywhere)
		TArray<FWealthURL> WealthURL;
};

#pragma endregion

#pragma region UIFrame
//布局类型
UENUM()
enum class ELayoutType : uint8 {
	Canvas,     //对应CanvasPanel
	Overlay,	//对应Overlay
};

//UI层级类型, 自己动态添加, 一般6层够用了
UENUM()
enum class ELayoutLevel : uint8
{
	Level_0 = 0,
	Level_1,
	Level_2,
	Level_3,
	Level_All,//这个层级会隐藏所有ShowGroup的对象
};


//面板类型
UENUM()
enum class EPanelShowType : uint8 {
	DoNothing,   //不影响其他面板
	HideOther,   //隐藏其他
	Reverse,     //反向切换, 弹窗类型
};

//弹窗遮罩透明度
UENUM()
enum class EPanelLucenyType : uint8 {
	Lucency,        //全透明, 不能穿透
	Translucence,   //半透明，不能穿透
	ImPenetrable,   //低透明度，不能穿透
	Pentrate,       //全透明, 可以穿透
};

//面板属性
USTRUCT()
struct FUINature
{
	GENERATED_BODY()

public:

	//布局类型
	UPROPERTY(EditAnywhere)
		ELayoutType LayoutType;

	//UI层级, 给HideOther类型的面板使用, 指定影响的范围
	UPROPERTY(EditAnywhere)
		ELayoutLevel LayoutLevel;

	//面板类型
	UPROPERTY(EditAnywhere)
		EPanelShowType PanelShowType;

	//弹窗遮罩透明度
	UPROPERTY(EditAnywhere)
		EPanelLucenyType PanelLucenyType;

	//Canvas锚点
	UPROPERTY(EditAnywhere)
		FAnchors Anchors;

	//Canvas的Offset(pos, size)  Overlay的padding
	UPROPERTY(EditAnywhere)
		FMargin Offsets;

	//Overlay的水平布局
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EHorizontalAlignment> HAlign;

	//Overlay的垂直布局
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EVerticalAlignment> VAlign;

};

#pragma endregion
