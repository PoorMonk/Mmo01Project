# Mmo游戏开发

## 一 登录模块

### 服务端

#### 1 创建服务器项目工程

通过new_assets.bat生成新的资产文件夹，重命名为Mmo01_assets。打开文件夹中gensdk.bat，注释掉生成u3d插件的部分（在前面加::）。

#### 2 创建并配置新的数据库

```mysql
$create database mmo01db;
$use mysql;
$delete from user where user='';
$flush privileges;
$grant all privileges on mmo01db.* to kbeuser@'%' identified by 'kbeuser123';
$grant select,insert,update,delete,create,drop on mmo01db.* to kbeuser@'%' identified by 'kbeuser123';
$flush privileges;
$quit;
```

修改course_assets\res\server下的kbengine.xml文件, 将KBEngine\kbe\res\server下的kbengine_defaults.xml里的数据库相关配置内容赋值粘贴, 并且修改数据库名为mmo01db, **设置自动注册为loginAutoCreate为false**。

![](D:\Unreal\UnrealProjects\C++\Mmo01Project\Docs\pics\01.png)

#### 3 创建用户入口实体

服务端会自带一个Account实体，可以根据自己需要来修改。要记得修改配置文件，在Mmo01_assets/res/server/kbengine.xml中，修改dbmgr部分，如果没有则添加该部分：

```mysql
<root>
    ...
    <dbmgr>
        <account_system>
            <accountEntityScriptType>	Account	</accountEntityScriptType>
        </account_system>
    </dbmgr>
    ...
</root>
```

#### 4 生成UE4插件

双击gensdk.bat即可，把生成的插件放入UE4项目的Plugins中。

### 客户端

#### 1 继承服务端生成的实体创建对应的类

实现构造析构以及重写 __ init __ ()与onDestroy()函数,  __ init__()函数内触发登陆成功事件

```c++
void KBEngine::FirstEntity::__init__()
{
	UKBEventData_onLoginSuccessfully* EventData = NewObject<UKBEventData_onLoginSuccessfully>();
	EventData->entity_id = id();
	EventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
    
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", EventData);
}

void KBEngine::FirstEntity::onDestroy()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}
```

#### 2 登录模块需要创建LoginGameMode、LoginPlayerController、LoginWidget

不同的模块都需要单独的GameMode，可以抽象出一个基类，实现和KBE有关的事件。

```c++
void AKbeBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	InstallEvent();
}

void AKbeBaseGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnInstallEvent();
}

void AKbeBaseGameMode::InstallEvent()
{
	//注册最基本的回调事件
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);
}

void AKbeBaseGameMode::UnInstallEvent()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}
```

还可以实现断线重连功能

```c++
void AKbeBaseGameMode::StartReloginBaseapp()
{
	if (!ReloginHandle.IsValid())
	{
        // 一秒重连一次
		GetWorld()->GetTimerManager().SetTimer(ReloginHandle, this, &AKbeBaseGameMode::OnReloginBaseapp, 1.f, true, 1.f);
	}
}

void AKbeBaseGameMode::StopReloginBaseapp()
{
    // 重连成功关闭定时器
	if (ReloginHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloginHandle);
	}
}

void AKbeBaseGameMode::OnReloginBaseapp()
{
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();
}
```

##### a 创建一个kbeClientActor

这个Actor就包含一个UKBEMain对象，用来填和服务端通信的信息（IP、Port等）

```c++
AKbeClientActor::AKbeClientActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	KbeMain = CreateDefaultSubobject<UKBEMain>(TEXT("KbeMain"));
}
```

##### b 创建属于登录模块的PlayerController

主要是用来设置UI模式和屏幕宽高

```c++
void ALoginController::BeginPlay()
{
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
	
	bShowMouseCursor = true;

	// 设置游戏窗口大小
	ConsoleCommand(FString::Printf(TEXT("r.setres %dx%dw"), ScreenWidth, ScreenHeight));
}
```

##### c 创建登录的UI界面

实现登录和注册按钮功能（通过KBMain调用相应的功能）

```c++
void ULoginWidget::RegisterOrLogin(bool isLogin)
{
	FString username = EditText_Username->GetText().ToString();;
	FString password = EditText_Password->GetText().ToString();;
	TArray<uint8> Params;
	
	if (username.IsEmpty() || password.IsEmpty())
	{
		HFH::Debug() << "username or password is null" << HFH::Endl();
		return;
	}

	FString name = "MmoProject";
	for (int i = 0; i < name.Len(); ++i)
	{
		Params.Add((uint8)name[i]);
	}

	if (isLogin)
	{
		MmoLoginGameMode->KbeMain->login(username, password, Params);
	}
	else
	{
		MmoLoginGameMode->KbeMain->createAccount(username, password, Params);
	}
}
```

##### d 创建登录用的GameMode

保存两个变量kbeMain和LoginWidget，kbeMain的获得可以通过全局迭代搜索。

```c++
void ALoginGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (LoginWidgetClass)
	{
		MmoLoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
		MmoLoginWidget->MmoLoginGameMode = this;
		MmoLoginWidget->AddToViewport();
	}

	for (TActorIterator<AKbeClientActor> ActItem(GetWorld()); ActItem; ++ActItem)
	{
		KbeMain = (*ActItem)->KbeMain;
	}
}
```

注册相关事件

```c++
void ALoginGameMode::InstallEvent()
{
	// 每次进入到登录界面先清理一次KBE，否则KBE插件缓存内容一直存在
	KBEngine::KBEngineApp::getSingleton().reset();

	Super::InstallEvent();

	//创建用户入口实体回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	//登陆失败回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	//版本匹配回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	//版本不匹配回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	//登陆baseapp失败回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	//登陆baseapp回调
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
    
	//登陆成功回调函数, 生成ExAccount后在__init__()时调用, 在这里跳转到选择角色场景
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);
}
```

登录成功后会执行回调函数，可以在回调函数里跳转到下一模块

```c++
void ALoginGameMode::OnLoginSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginSuccessfully* ServerData = Cast<UKBEventData_onLoginSuccessfully>(pEventData);

	HFH::Debug() << "OnLoginSuccessfully : entity_uuid --> " << ServerData->entity_uuid << " ; entity_id --> " << ServerData->entity_id << HFH::Endl();

	UGameplayStatics::OpenLevel(GetWorld(), FName("RoomMap"));
}
```







