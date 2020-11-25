// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HFTypes.h"
#include "HFDefine.generated.h"

/**
 * 
 */
UCLASS()
class HFDATADRIVEN_API UHFDefine : public UObject
{
	GENERATED_BODY()
	
};

#define HFMODFUNC(FuncName); \
	struct FuncName##Param : public HFParam \
	{\
		FuncName##Param() { ParamPtr = nullptr; }\
	};\
	void FuncName(int32 ModuIndex, FName FunctionName)\
	{\
		HFModuleAgreement Agreement;\
		Agreement.ModuleIndex = ModuIndex;\
		Agreement.FunctionName = FunctionName;\
		FuncName##Param* Param = new FuncName##Param();\
		ExecuteFunction(Agreement, Param);\
		delete Param;\
	}\
	FuncName##Param* FuncName##Rt(int32 ModuIndex, FName FunctionName)\
	{\
		HFModuleAgreement Agreement;\
		Agreement.ModuleIndex = ModuIndex;\
		Agreement.FunctionName = FunctionName;\
		FuncName##Param* Param = new FuncName##Param();\
		ExecuteFunction(Agreement, Param);\
		return Param;\
	}

#define HFMODFUNC_ONE(FuncName, ParamType1, ParamName1); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_TWO(FuncName, ParamType1, ParamName1, ParamType2, ParamName2); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_THREE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_FOUR(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_FIVE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_SIX(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_SEVEN(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_EIGHT(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_NINE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8, ParamType9, ParamName9); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
			ParamType9 ParamName9; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		ParamType9 ParamName9() { return Parameter.ParamName9; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFMODFUNC_TEN(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8, ParamType9, ParamName9, ParamType10, ParamName10); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
			ParamType9 ParamName9; \
			ParamType10 ParamName10; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		ParamType9 ParamName9() { return Parameter.ParamName9; } \
		ParamType10 ParamName10() { return Parameter.ParamName10; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		HFModuleAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}



#define HFOBJFUNC(FuncName); \
	struct FuncName##Param : HFParam \
	{ \
		FuncName##Param() { ParamPtr = NULL; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_ONE(FuncName, ParamType1, ParamName1); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_TWO(FuncName, ParamType1, ParamName1, ParamType2, ParamName2); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}



#define HFOBJFUNC_THREE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_FOUR(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_FIVE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_SIX(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_SEVEN(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_EIGHT(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_NINE(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8, ParamType9, ParamName9); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
			ParamType9 ParamName9; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		ParamType9 ParamName9() { return Parameter.ParamName9; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}


#define HFOBJFUNC_TEN(FuncName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4, ParamType5, ParamName5, ParamType6, ParamName6, ParamType7, ParamName7, ParamType8, ParamName8, ParamType9, ParamName9, ParamType10, ParamName10); \
	struct FuncName##Param : HFParam \
	{ \
		struct \
		{ \
			ParamType1 ParamName1; \
			ParamType2 ParamName2; \
			ParamType3 ParamName3; \
			ParamType4 ParamName4; \
			ParamType5 ParamName5; \
			ParamType6 ParamName6; \
			ParamType7 ParamName7; \
			ParamType8 ParamName8; \
			ParamType9 ParamName9; \
			ParamType10 ParamName10; \
		} Parameter; \
		ParamType1 ParamName1() { return Parameter.ParamName1; } \
		ParamType2 ParamName2() { return Parameter.ParamName2; } \
		ParamType3 ParamName3() { return Parameter.ParamName3; } \
		ParamType4 ParamName4() { return Parameter.ParamName4; } \
		ParamType5 ParamName5() { return Parameter.ParamName5; } \
		ParamType6 ParamName6() { return Parameter.ParamName6; } \
		ParamType7 ParamName7() { return Parameter.ParamName7; } \
		ParamType8 ParamName8() { return Parameter.ParamName8; } \
		ParamType9 ParamName9() { return Parameter.ParamName9; } \
		ParamType10 ParamName10() { return Parameter.ParamName10; } \
		FuncName##Param() { ParamPtr = &Parameter; } \
	};\
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	FuncName##Param* FuncName##RT(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ExecuteFunction(Agreement, Param); \
		return Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, TArray<FName> ObjectGroup, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup = ObjectGroup; \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, EAgreementType AgreementType, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = AgreementType; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	} \
	void FuncName(int32 ModuIndex, FName ObjName, FName FunctionName, ParamType1 ParamName1, ParamType2 ParamName2, ParamType3 ParamName3, ParamType4 ParamName4, ParamType5 ParamName5, ParamType6 ParamName6, ParamType7 ParamName7, ParamType8 ParamName8, ParamType9 ParamName9, ParamType10 ParamName10) \
	{ \
		HFObjectAgreement Agreement; \
		Agreement.ModuleIndex = ModuIndex; \
		Agreement.AgreementType = EAgreementType::SelfObject; \
		Agreement.ObjectGroup.Add(ObjName); \
		Agreement.FunctionName = FunctionName; \
		FuncName##Param* Param = new FuncName##Param(); \
		Param->Parameter.ParamName1 = ParamName1; \
		Param->Parameter.ParamName2 = ParamName2; \
		Param->Parameter.ParamName3 = ParamName3; \
		Param->Parameter.ParamName4 = ParamName4; \
		Param->Parameter.ParamName5 = ParamName5; \
		Param->Parameter.ParamName6 = ParamName6; \
		Param->Parameter.ParamName7 = ParamName7; \
		Param->Parameter.ParamName8 = ParamName8; \
		Param->Parameter.ParamName9 = ParamName9; \
		Param->Parameter.ParamName10 = ParamName10; \
		ExecuteFunction(Agreement, Param); \
		delete Param; \
	}
