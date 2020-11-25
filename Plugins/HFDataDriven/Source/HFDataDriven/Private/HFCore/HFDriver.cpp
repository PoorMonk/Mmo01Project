// Fill out your copyright notice in the Description page of Project Settings.


#include "HFCore/HFDriver.h"
#include "Kismet/GameplayStatics.h"
#include "HFObject/HFOOInterface.h"

// Sets default values
AHFDriver::AHFDriver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	Center = CreateDefaultSubobject<UHFCenterModule>(TEXT("Center"));
	Center->SetupAttachment(RootComponent);

	IsBeginPlay = false;
}

void AHFDriver::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//注册Driver到UHFCommon单例
	UHFCommon::Get()->InitDriver(this);
	//在游戏运行之前进行一次模组ID的设定，在这里面会注册子模组到数组
	Center->IterChangeModuleType(Center, ModuleType);
	//指定完模组ID后收集模组到总数组
	Center->TotalGatherModule(ModuleType);
	//创建所有模组的模块
	Center->IterCreateManager(Center);
}

bool AHFDriver::RegisterToModule(IHFOOInterface* ObjectInst)
{
	return Center->RegisterToModule(ObjectInst);
}

void AHFDriver::ExecuteFunction(HFModuleAgreement Agreement, HFParam* Param)
{
	Center->AllowExecuteFunction(Agreement, Param);
}

void AHFDriver::ExecuteFunction(HFObjectAgreement Agreement, HFParam* Param)
{
	Center->AllowExecuteFunction(Agreement, Param);
}

#if WITH_EDITOR
void AHFDriver::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName()
		== GET_MEMBER_NAME_CHECKED(AHFDriver, ModuleType))
	{
		Center->IterChangeModuleType(Center, ModuleType);
	}
}
#endif

// Called when the game starts or when spawned
void AHFDriver::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterGamePlay();

	Center->IterModuleInit(Center);
}

void AHFDriver::RegisterGamePlay()
{
	//获取GameInstance
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());

	if (GameInstance && Cast<IHFOOInterface>(GameInstance))
	{
		Cast<IHFOOInterface>(GameInstance)->RegisterToModule("Center", "GameInstance", "GameInstance");
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		HFH::Debug() << "No PlayerController" << HFH::Endl();
	}
	else
	{
		UHFCommon::Get()->InitController(PlayerController);
	}
}

// Called every frame
void AHFDriver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsBeginPlay)
	{
		Center->IterModuleBeginPlay(Center);
		IsBeginPlay = true;
	}
	else
	{
		Center->IterModuleTick(Center, DeltaTime);
	}
}


