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

//����Զ���Debug�����
#pragma region LogDebug
class HFDATADRIVEN_API HFRecord
{
public:
	inline HFRecord() { }
	~HFRecord() { }

	static TSharedPtr<HFRecord> Get();

	//���ò���
	inline void InitParam(float time, FColor color)
	{
		ShowTime = time;
		ShowColor = color;
	}

	//ִ�д�ӡ����
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

	//��д������
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

	//�������(���������Ϊ������ִ���������������)
	//HFRecord::Get() << FString("haha") << FName("Harkey") << int << float << HFRecord::Get();

public:
	//��ӡģʽ��0��debug��1��log��2��Warning��3��Error
	uint8 PatternID;

private:
	//��������
	static TSharedPtr<HFRecord> RecordInst;

	//���ɵ��ַ���
	FString RecordInfo;
	//��ʾʱ��
	float ShowTime;
	//��ʾ��ɫ
	FColor ShowColor;
};
#pragma endregion

#pragma region LifeTimePart
//��������
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

//����״̬
UENUM()
enum class EBaseObjectState : uint8
{
	Active = 0,		//����״̬
	Stable,			//�ȶ�״̬
	Destroy			//����״̬
};
#pragma endregion

#pragma region ReflectPart
//�������Э��
UENUM()
enum class EAgreementType : uint8
{
	SelfObject,			//������Ķ���ͨ��
	OtherObject,		//������Ķ���֮��Ķ���ͨ��
	ClassOtherObject,	//������Ķ������ͬ�����������ͨ��
	SelfClass,			//�������Ķ���ͨ��
	OtherClass,			//��������ͨ��
	All					//�����еĶ���ͨ��
};

//���ý��
UENUM()
enum class ECallResult : uint8
{
	NoModule = 0,	//ȱʧģ��
	LackObject,		//ȱʧ���ֶ���
	NoFunction,		//ȱʧ����
	Succeed			//���óɹ�
};

//ͨ�Ų����ṹ�����
struct HFParam
{
public:
	//���ý��
	ECallResult CallResult;

	//����ָ��
	void* ParamPtr;
};

//ͨ��Э�飬Module����
struct  HFModuleAgreement
{
public:
	//ģ��ID
	int32 ModuleIndex;

	//������
	FName FunctionName;
};

//ͨ��Э�飬 HFOOInterface����
struct HFObjectAgreement
{
public:
	//ģ��ID
	int32 ModuleIndex;

	//Э������
	EAgreementType AgreementType;

	//��������
	TArray<FName> ObjectGroup;

	//������
	FName FunctionName;
};

#pragma endregion

#pragma region HFAnyFunc
//�洢�������͵ĺ���
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
//�洢�������͵����ݽṹ
struct AnyElement
{
	//Ԫ�ظ��ṹ��
	struct BaseElement
	{
	public:
		virtual ~BaseElement() { }
	};
	//ʵ�ʴ洢ֵ�ýṹ��
	template<typename T>
	struct ValueElement : public BaseElement
	{
	public:
		T Value;
		ValueElement(const T& InValue) : Value(InValue) { }
	};
	//���ṹ��ָ�룬���ڴ洢ʵ�������ӽṹ��ĵ�ַ
	BaseElement* ElementPtr;

public:
	AnyElement() : ElementPtr(nullptr) { }
	//���캯������ֵ����ʵ�����ӽṹ��洢�ڸ��ṹ��ָ��
	template<typename T>
	AnyElement(const T& InValue) : ElementPtr(new ValueElement<T>(InValue)) { }
	~AnyElement() { if (ElementPtr) delete ElementPtr; }
	//��ȡ����ı���
	template<typename T>
	T& Get()
	{
		ValueElement<T>* SubPtr = static_cast<ValueElement<T>*>(ElementPtr);
		return SubPtr->Value;
	}
};
#pragma endregion

#pragma region MsgNode
//�¼��ڵ�
struct HFMsgNode
{
	//�����õĽӿ�����
	int32 CallCount;
	//�����б�
	TMap<int32, HFAnyFunc*> FuncQueue;
	//ע�᷽��
	template<typename RetType, typename... VarTypes>
	int32 RegisterFunc(TFunction<RetType(VarTypes...)> InsFunc);
	//ע������
	void UnRegisterFunc(int32 FuncID)
	{
		//���б��Ƴ�����
		HFAnyFunc* DesPtr = *FuncQueue.Find(FuncID);
		FuncQueue.Remove(FuncID);
		delete DesPtr;
	}
	//��սڵ�
	void ClearNode()
	{
		for (TMap<int32, HFAnyFunc*>::TIterator It(FuncQueue); It; ++It)
		{
			delete It.Value();
		}
	}
	//ִ�з���
	template<typename RetType, typename... VarTypes>
	RetType Execute(VarTypes... Params);
	//�ж��Ƿ��а󶨺���
	bool IsBound() { return FuncQueue.Num() > 0; }
	//ִ�а󶨷���
	template<typename RetType, typename... VarTypes>
	bool ExecuteIfBound(VarTypes... Params);

	HFMsgNode() : CallCount(0) { }
};

template<typename RetType, typename... VarTypes>
int32 HFMsgNode::RegisterFunc(TFunction<RetType(VarTypes...)> InsFunc)
{
	//��ȡ����������������±�
	TArray<int32> FuncKeyQuene;
	FuncQueue.GenerateKeyArray(FuncKeyQuene);
	//��ȡ���±�
	int32 NewID;
	for (int32 i = FuncKeyQuene.Num(); i >= 0; --i)
	{
		if (!FuncKeyQuene.Contains(i))
		{
			NewID = i;
			break;
		}
	}
	//���·�����ӵ��ڵ�
	FuncQueue.Add(NewID, new HFAnyFunc(InsFunc));
	return NewID;
}

template<typename RetType, typename... VarTypes>
RetType HFMsgNode::Execute(VarTypes... Params)
{
	//�����ڶ��������һ��
	TMap<int32, HFAnyFunc*>::TIterator It(FuncQueue);
	++It;
	for (; It; ++It)
	{
		It.Value()->Execute<RetType, VarTypes...>(Params...);
	}
	//��ȡ��һ������
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
	//�¼�����
	HFMsgQueue* MsgQueue;
	//�ڵ�����������
	FName CallName;
	//�Ƿ���Ч,������д���ڲ���������״̬
	TSharedPtr<bool> IsActived;
	//ִ�з���
	RetType Execute(VarTypes... Params);
	//�Ƿ��Ѿ���
	bool IsBound();
	//ִ�а󶨺���
	bool ExecuteIfBound(VarTypes... Params);
	//ע�����ýӿ�
	void UnRegister();

	HFCallHandle() { }

	HFCallHandle(HFMsgQueue* MQ, FName CN)
	{
		MsgQueue = MQ;
		CallName = CN;
		IsActived = MakeShareable<bool>(new bool(true));
	}

	//��д������
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
	//�ڵ�����
	TMap<FName, HFMsgNode> MsgQueue;
	//ע����ýӿ�
	template<typename RetType, typename... VarTypes>
	HFCallHandle<RetType, VarTypes...> RegisterCallPort(FName CallName);
	//ע�᷽���ӿ�
	template<typename RetType, typename... VarTypes>
	HFFuncHandle RegisterFuncPort(FName CallName, TFunction<RetType(VarTypes...)> InsFunc);
	//�Ƴ����ýӿ�
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
	//ע�������ӿ�
	void UnRegisterFuncPort(FName CallName, int32 FuncID)
	{
		if (!MsgQueue.Contains(CallName))
		{
			return;
		}
		MsgQueue.Find(CallName)->UnRegisterFunc(FuncID);
	}
	//ִ�з����ӿ�
	template<typename RetType, typename... VarTypes>
	RetType Execute(FName CallName, VarTypes... Params);
	//�Ƿ��Ѿ��󶨷���
	bool IsBound(FName CallName) { return MsgQueue.Find(CallName)->IsBound(); }
};

template<typename RetType, typename... VarTypes>
HFCallHandle<RetType, VarTypes...>
HFMsgQueue::RegisterCallPort(FName CallName)
{
	//����Ѿ����ڶ�ӦCallName�ĵ��ýӿڣ��ͰѼ�����+1
	if (MsgQueue.Contains(CallName))
	{
		MsgQueue.Find(CallName)->CallCount++;
	}
	else
	{
		//�����µ��¼��ڵ㲢��ӵ�����
		MsgQueue.Add(CallName, HFMsgNode());
		//��������1
		MsgQueue.Find(CallName)->CallCount++;
	}
	//���ص��þ��
	return HFCallHandle<RetType, VarTypes...>(this, CallName);
}

template<typename RetType, typename... VarTypes>
HFFuncHandle HFMsgQueue::RegisterFuncPort(FName CallName, TFunction<RetType(VarTypes...)> InsFunc)
{
	//��ȡ�µķ����±�
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
	//��Ϣ����
	HFMsgQueue* MsgQueue;
	//��������
	FName CallName;
	//����ID
	int32 FuncID;
	//�Ƿ���Ч
	TSharedPtr<bool> IsActived;
	//ע������
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
	//������
	UPROPERTY(EditAnywhere)
		FName ObjectName;
	//����
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

//Object��Դ�ṹ��
USTRUCT()
struct FObjectWealthEntry 
{
	GENERATED_BODY()

public:
	//��Դ��
	UPROPERTY(EditAnywhere)
		FName WealthName;
	//��Դ������
	UPROPERTY(EditAnywhere)
		FName WealthKind;
	//��Դ����
	UPROPERTY(EditAnywhere)
		FStringAssetReference WealthPath;
	//���س����Ķ���
	UPROPERTY()
		UObject* WealthObj;
};

//UClass����ö��
UENUM()
enum class EWealthType : uint8
{
	Object,
	Actor,
	Widget
};

//Class��Դ�ṹ��
USTRUCT()
struct FClassWealthEntry 
{
	GENERATED_BODY()

public:
	//��Դ��
	UPROPERTY(EditAnywhere)
		FName WealthName;
	//��Դ������
	UPROPERTY(EditAnywhere)
		FName WealthKind;
	//��Դ���
	UPROPERTY(EditAnywhere)
		EWealthType WealthType;
	//��Դ����
	UPROPERTY(EditAnywhere)
		TSoftClassPtr<UObject> WealthPtr;
	//���س����Ķ���
	UPROPERTY()
		UClass* WealthClass;
};

//����ȡ���ӽṹ�壬������ͬ�첽����
USTRUCT()
struct FWealthURL 
{
	GENERATED_BODY()

public:
	//��Դ��
	UPROPERTY(EditAnywhere)
		FName WealthName;

	//��Դ������
	UPROPERTY(EditAnywhere)
		FName WealthKind;

	//��Դ����
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
	//ģ�����֣�Ĭ��ע�ᵽModuleName��Ӧ��ģ�飬���Ϊ�ձ�ʾʹ���ڶ��ģ����
	UPROPERTY(EditAnywhere)
		FName ModuleName;

	//�Զ����ɵĶ���
	UPROPERTY(EditAnywhere)
		TArray<FWealthObject> AutoObjectData;

	//�Զ����ɵ�Actor
	UPROPERTY(EditAnywhere)
		TArray<FWealthActor> AutoActorData;

	//�Զ����ɵ�Widget
	UPROPERTY(EditAnywhere)
		TArray<FWealthWidget> AutoWidgetData;

	//Object��Դ���Ӽ���
	UPROPERTY(EditAnywhere)
		TArray<FObjectWealthEntry> ObjectWealthData;

	//Class��Դ���Ӽ���
	UPROPERTY(EditAnywhere)
		TArray<FClassWealthEntry> ClassWealthData;

	//��Դ���Ӽ���
	UPROPERTY(EditAnywhere)
		TArray<FWealthURL> WealthURL;
};

#pragma endregion

#pragma region UIFrame
//��������
UENUM()
enum class ELayoutType : uint8 {
	Canvas,     //��ӦCanvasPanel
	Overlay,	//��ӦOverlay
};

//UI�㼶����, �Լ���̬���, һ��6�㹻����
UENUM()
enum class ELayoutLevel : uint8
{
	Level_0 = 0,
	Level_1,
	Level_2,
	Level_3,
	Level_All,//����㼶����������ShowGroup�Ķ���
};


//�������
UENUM()
enum class EPanelShowType : uint8 {
	DoNothing,   //��Ӱ���������
	HideOther,   //��������
	Reverse,     //�����л�, ��������
};

//��������͸����
UENUM()
enum class EPanelLucenyType : uint8 {
	Lucency,        //ȫ͸��, ���ܴ�͸
	Translucence,   //��͸�������ܴ�͸
	ImPenetrable,   //��͸���ȣ����ܴ�͸
	Pentrate,       //ȫ͸��, ���Դ�͸
};

//�������
USTRUCT()
struct FUINature
{
	GENERATED_BODY()

public:

	//��������
	UPROPERTY(EditAnywhere)
		ELayoutType LayoutType;

	//UI�㼶, ��HideOther���͵����ʹ��, ָ��Ӱ��ķ�Χ
	UPROPERTY(EditAnywhere)
		ELayoutLevel LayoutLevel;

	//�������
	UPROPERTY(EditAnywhere)
		EPanelShowType PanelShowType;

	//��������͸����
	UPROPERTY(EditAnywhere)
		EPanelLucenyType PanelLucenyType;

	//Canvasê��
	UPROPERTY(EditAnywhere)
		FAnchors Anchors;

	//Canvas��Offset(pos, size)  Overlay��padding
	UPROPERTY(EditAnywhere)
		FMargin Offsets;

	//Overlay��ˮƽ����
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EHorizontalAlignment> HAlign;

	//Overlay�Ĵ�ֱ����
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EVerticalAlignment> VAlign;

};

#pragma endregion
