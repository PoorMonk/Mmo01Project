#include "EntityDef.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "KBVar.h"
#include "Entity.h"

#include "Scripts/FirstEntity.h"
#include "Scripts/Role.h"

namespace KBEngine
{

TMap<FString, uint16> EntityDef::datatype2id;
TMap<FString, DATATYPE_BASE*> EntityDef::datatypes;
TMap<uint16, DATATYPE_BASE*> EntityDef::id2datatypes;
TMap<FString, int32> EntityDef::entityclass;
TMap<FString, ScriptModule*> EntityDef::moduledefs;
TMap<uint16, ScriptModule*> EntityDef::idmoduledefs;

bool EntityDef::initialize()
{
	initDataTypes();
	initDefTypes();
	initScriptModules();
	return true;
}

bool EntityDef::reset()
{
	clear();
	return initialize();
}

void EntityDef::clear()
{
	TArray<DATATYPE_BASE*> deleted_datatypes;
	for (auto& item : EntityDef::datatypes)
	{
		int32 idx = deleted_datatypes.Find(item.Value);
		if (idx != INDEX_NONE)
			continue;

		deleted_datatypes.Add(item.Value);
		delete item.Value;
	}

	for (auto& item : EntityDef::moduledefs)
		delete item.Value;

	datatype2id.Empty();
	datatypes.Empty();
	id2datatypes.Empty();
	entityclass.Empty();
	moduledefs.Empty();
	idmoduledefs.Empty();
}

void EntityDef::initDataTypes()
{
	datatypes.Add(TEXT("UINT8"), new DATATYPE_UINT8());
	datatypes.Add(TEXT("UINT16"), new DATATYPE_UINT16());
	datatypes.Add(TEXT("UINT32"), new DATATYPE_UINT32());
	datatypes.Add(TEXT("UINT64"), new DATATYPE_UINT64());

	datatypes.Add(TEXT("INT8"), new DATATYPE_INT8());
	datatypes.Add(TEXT("INT16"), new DATATYPE_INT16());
	datatypes.Add(TEXT("INT32"), new DATATYPE_INT32());
	datatypes.Add(TEXT("INT64"), new DATATYPE_INT64());

	datatypes.Add(TEXT("FLOAT"), new DATATYPE_FLOAT());
	datatypes.Add(TEXT("DOUBLE"), new DATATYPE_DOUBLE());

	datatypes.Add(TEXT("STRING"), new DATATYPE_STRING());
	datatypes.Add(TEXT("VECTOR2"), new DATATYPE_VECTOR2());

	datatypes.Add(TEXT("VECTOR3"), new DATATYPE_VECTOR3());

	datatypes.Add(TEXT("VECTOR4"), new DATATYPE_VECTOR4());
	datatypes.Add(TEXT("PYTHON"), new DATATYPE_PYTHON());

	datatypes.Add(TEXT("UNICODE"), new DATATYPE_UNICODE());
	datatypes.Add(TEXT("ENTITYCALL"), new DATATYPE_ENTITYCALL());

	datatypes.Add(TEXT("BLOB"), new DATATYPE_BLOB());
}

Entity* EntityDef::createEntity(int utype)
{
	Entity* pEntity = NULL;

	switch(utype)
	{
		case 1:
			pEntity = new FirstEntity();
			break;
		case 4:
			pEntity = new Role();
			break;
		default:
			SCREEN_ERROR_MSG("EntityDef::createEntity() : entity(%d) not found!", utype);
			break;
	};

	return pEntity;
}

void EntityDef::initScriptModules()
{
	ScriptModule* pFirstEntityModule = new ScriptModule("FirstEntity", 1);
	EntityDef::moduledefs.Add(TEXT("FirstEntity"), pFirstEntityModule);
	EntityDef::idmoduledefs.Add(1, pFirstEntityModule);

	Property* pFirstEntity_position = new Property();
	pFirstEntity_position->name = TEXT("position");
	pFirstEntity_position->properUtype = 40000;
	pFirstEntity_position->properFlags = 4;
	pFirstEntity_position->aliasID = 1;
	KBVar* pFirstEntity_position_defval = new KBVar(FVector());
	pFirstEntity_position->pDefaultVal = pFirstEntity_position_defval;
	pFirstEntityModule->propertys.Add(TEXT("position"), pFirstEntity_position); 

	pFirstEntityModule->usePropertyDescrAlias = true;
	pFirstEntityModule->idpropertys.Add((uint16)pFirstEntity_position->aliasID, pFirstEntity_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), property(position / 40000).");

	Property* pFirstEntity_direction = new Property();
	pFirstEntity_direction->name = TEXT("direction");
	pFirstEntity_direction->properUtype = 40001;
	pFirstEntity_direction->properFlags = 4;
	pFirstEntity_direction->aliasID = 2;
	KBVar* pFirstEntity_direction_defval = new KBVar(FVector());
	pFirstEntity_direction->pDefaultVal = pFirstEntity_direction_defval;
	pFirstEntityModule->propertys.Add(TEXT("direction"), pFirstEntity_direction); 

	pFirstEntityModule->usePropertyDescrAlias = true;
	pFirstEntityModule->idpropertys.Add((uint16)pFirstEntity_direction->aliasID, pFirstEntity_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), property(direction / 40001).");

	Property* pFirstEntity_spaceID = new Property();
	pFirstEntity_spaceID->name = TEXT("spaceID");
	pFirstEntity_spaceID->properUtype = 40002;
	pFirstEntity_spaceID->properFlags = 16;
	pFirstEntity_spaceID->aliasID = 3;
	KBVar* pFirstEntity_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pFirstEntity_spaceID->pDefaultVal = pFirstEntity_spaceID_defval;
	pFirstEntityModule->propertys.Add(TEXT("spaceID"), pFirstEntity_spaceID); 

	pFirstEntityModule->usePropertyDescrAlias = true;
	pFirstEntityModule->idpropertys.Add((uint16)pFirstEntity_spaceID->aliasID, pFirstEntity_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), property(spaceID / 40002).");

	TArray<DATATYPE_BASE*> FirstEntity_OnReqRoleList_args;
	FirstEntity_OnReqRoleList_args.Add(EntityDef::id2datatypes[24]);

	Method* pFirstEntity_OnReqRoleList = new Method();
	pFirstEntity_OnReqRoleList->name = TEXT("OnReqRoleList");
	pFirstEntity_OnReqRoleList->methodUtype = 10;
	pFirstEntity_OnReqRoleList->aliasID = 1;
	pFirstEntity_OnReqRoleList->args = FirstEntity_OnReqRoleList_args;

	pFirstEntityModule->methods.Add(TEXT("OnReqRoleList"), pFirstEntity_OnReqRoleList); 
	pFirstEntityModule->useMethodDescrAlias = true;
	pFirstEntityModule->idmethods.Add((uint16)pFirstEntity_OnReqRoleList->aliasID, pFirstEntity_OnReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(OnReqRoleList / 10).");

	TArray<DATATYPE_BASE*> FirstEntity_OnReqRoomList_args;
	FirstEntity_OnReqRoomList_args.Add(EntityDef::id2datatypes[27]);

	Method* pFirstEntity_OnReqRoomList = new Method();
	pFirstEntity_OnReqRoomList->name = TEXT("OnReqRoomList");
	pFirstEntity_OnReqRoomList->methodUtype = 8;
	pFirstEntity_OnReqRoomList->aliasID = 2;
	pFirstEntity_OnReqRoomList->args = FirstEntity_OnReqRoomList_args;

	pFirstEntityModule->methods.Add(TEXT("OnReqRoomList"), pFirstEntity_OnReqRoomList); 
	pFirstEntityModule->useMethodDescrAlias = true;
	pFirstEntityModule->idmethods.Add((uint16)pFirstEntity_OnReqRoomList->aliasID, pFirstEntity_OnReqRoomList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(OnReqRoomList / 8).");

	TArray<DATATYPE_BASE*> FirstEntity_OnSelectRole_args;
	FirstEntity_OnSelectRole_args.Add(EntityDef::id2datatypes[2]);
	FirstEntity_OnSelectRole_args.Add(EntityDef::id2datatypes[5]);

	Method* pFirstEntity_OnSelectRole = new Method();
	pFirstEntity_OnSelectRole->name = TEXT("OnSelectRole");
	pFirstEntity_OnSelectRole->methodUtype = 11;
	pFirstEntity_OnSelectRole->aliasID = 3;
	pFirstEntity_OnSelectRole->args = FirstEntity_OnSelectRole_args;

	pFirstEntityModule->methods.Add(TEXT("OnSelectRole"), pFirstEntity_OnSelectRole); 
	pFirstEntityModule->useMethodDescrAlias = true;
	pFirstEntityModule->idmethods.Add((uint16)pFirstEntity_OnSelectRole->aliasID, pFirstEntity_OnSelectRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(OnSelectRole / 11).");

	TArray<DATATYPE_BASE*> FirstEntity_OnSelectRoom_args;

	Method* pFirstEntity_OnSelectRoom = new Method();
	pFirstEntity_OnSelectRoom->name = TEXT("OnSelectRoom");
	pFirstEntity_OnSelectRoom->methodUtype = 9;
	pFirstEntity_OnSelectRoom->aliasID = 4;
	pFirstEntity_OnSelectRoom->args = FirstEntity_OnSelectRoom_args;

	pFirstEntityModule->methods.Add(TEXT("OnSelectRoom"), pFirstEntity_OnSelectRoom); 
	pFirstEntityModule->useMethodDescrAlias = true;
	pFirstEntityModule->idmethods.Add((uint16)pFirstEntity_OnSelectRoom->aliasID, pFirstEntity_OnSelectRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(OnSelectRoom / 9).");

	TArray<DATATYPE_BASE*> FirstEntity_onEnter_args;

	Method* pFirstEntity_onEnter = new Method();
	pFirstEntity_onEnter->name = TEXT("onEnter");
	pFirstEntity_onEnter->methodUtype = 6;
	pFirstEntity_onEnter->aliasID = 5;
	pFirstEntity_onEnter->args = FirstEntity_onEnter_args;

	pFirstEntityModule->methods.Add(TEXT("onEnter"), pFirstEntity_onEnter); 
	pFirstEntityModule->useMethodDescrAlias = true;
	pFirstEntityModule->idmethods.Add((uint16)pFirstEntity_onEnter->aliasID, pFirstEntity_onEnter);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(onEnter / 6).");

	TArray<DATATYPE_BASE*> FirstEntity_onSay_args;
	FirstEntity_onSay_args.Add(EntityDef::id2datatypes[12]);

	Method* pFirstEntity_onSay = new Method();
	pFirstEntity_onSay->name = TEXT("onSay");
	pFirstEntity_onSay->methodUtype = 7;
	pFirstEntity_onSay->aliasID = 6;
	pFirstEntity_onSay->args = FirstEntity_onSay_args;

	pFirstEntityModule->methods.Add(TEXT("onSay"), pFirstEntity_onSay); 
	pFirstEntityModule->useMethodDescrAlias = true;
	pFirstEntityModule->idmethods.Add((uint16)pFirstEntity_onSay->aliasID, pFirstEntity_onSay);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(onSay / 7).");

	TArray<DATATYPE_BASE*> FirstEntity_ReqRoleList_args;

	Method* pFirstEntity_ReqRoleList = new Method();
	pFirstEntity_ReqRoleList->name = TEXT("ReqRoleList");
	pFirstEntity_ReqRoleList->methodUtype = 4;
	pFirstEntity_ReqRoleList->aliasID = -1;
	pFirstEntity_ReqRoleList->args = FirstEntity_ReqRoleList_args;

	pFirstEntityModule->methods.Add(TEXT("ReqRoleList"), pFirstEntity_ReqRoleList); 
	pFirstEntityModule->base_methods.Add(TEXT("ReqRoleList"), pFirstEntity_ReqRoleList);

	pFirstEntityModule->idbase_methods.Add(pFirstEntity_ReqRoleList->methodUtype, pFirstEntity_ReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(ReqRoleList / 4).");

	TArray<DATATYPE_BASE*> FirstEntity_ReqRoomList_args;

	Method* pFirstEntity_ReqRoomList = new Method();
	pFirstEntity_ReqRoomList->name = TEXT("ReqRoomList");
	pFirstEntity_ReqRoomList->methodUtype = 2;
	pFirstEntity_ReqRoomList->aliasID = -1;
	pFirstEntity_ReqRoomList->args = FirstEntity_ReqRoomList_args;

	pFirstEntityModule->methods.Add(TEXT("ReqRoomList"), pFirstEntity_ReqRoomList); 
	pFirstEntityModule->base_methods.Add(TEXT("ReqRoomList"), pFirstEntity_ReqRoomList);

	pFirstEntityModule->idbase_methods.Add(pFirstEntity_ReqRoomList->methodUtype, pFirstEntity_ReqRoomList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(ReqRoomList / 2).");

	TArray<DATATYPE_BASE*> FirstEntity_ReqSelectRole_args;
	FirstEntity_ReqSelectRole_args.Add(EntityDef::id2datatypes[5]);

	Method* pFirstEntity_ReqSelectRole = new Method();
	pFirstEntity_ReqSelectRole->name = TEXT("ReqSelectRole");
	pFirstEntity_ReqSelectRole->methodUtype = 5;
	pFirstEntity_ReqSelectRole->aliasID = -1;
	pFirstEntity_ReqSelectRole->args = FirstEntity_ReqSelectRole_args;

	pFirstEntityModule->methods.Add(TEXT("ReqSelectRole"), pFirstEntity_ReqSelectRole); 
	pFirstEntityModule->base_methods.Add(TEXT("ReqSelectRole"), pFirstEntity_ReqSelectRole);

	pFirstEntityModule->idbase_methods.Add(pFirstEntity_ReqSelectRole->methodUtype, pFirstEntity_ReqSelectRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(ReqSelectRole / 5).");

	TArray<DATATYPE_BASE*> FirstEntity_SelectRoom_args;
	FirstEntity_SelectRoom_args.Add(EntityDef::id2datatypes[5]);

	Method* pFirstEntity_SelectRoom = new Method();
	pFirstEntity_SelectRoom->name = TEXT("SelectRoom");
	pFirstEntity_SelectRoom->methodUtype = 3;
	pFirstEntity_SelectRoom->aliasID = -1;
	pFirstEntity_SelectRoom->args = FirstEntity_SelectRoom_args;

	pFirstEntityModule->methods.Add(TEXT("SelectRoom"), pFirstEntity_SelectRoom); 
	pFirstEntityModule->base_methods.Add(TEXT("SelectRoom"), pFirstEntity_SelectRoom);

	pFirstEntityModule->idbase_methods.Add(pFirstEntity_SelectRoom->methodUtype, pFirstEntity_SelectRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(SelectRoom / 3).");

	TArray<DATATYPE_BASE*> FirstEntity_say_args;
	FirstEntity_say_args.Add(EntityDef::id2datatypes[12]);

	Method* pFirstEntity_say = new Method();
	pFirstEntity_say->name = TEXT("say");
	pFirstEntity_say->methodUtype = 1;
	pFirstEntity_say->aliasID = -1;
	pFirstEntity_say->args = FirstEntity_say_args;

	pFirstEntityModule->methods.Add(TEXT("say"), pFirstEntity_say); 
	pFirstEntityModule->cell_methods.Add(TEXT("say"), pFirstEntity_say);

	pFirstEntityModule->idcell_methods.Add(pFirstEntity_say->methodUtype, pFirstEntity_say);

	//DEBUG_MSG("EntityDef::initScriptModules: add(FirstEntity), method(say / 1).");

	ScriptModule* pRoleModule = new ScriptModule("Role", 4);
	EntityDef::moduledefs.Add(TEXT("Role"), pRoleModule);
	EntityDef::idmoduledefs.Add(4, pRoleModule);

	Property* pRole_position = new Property();
	pRole_position->name = TEXT("position");
	pRole_position->properUtype = 40000;
	pRole_position->properFlags = 4;
	pRole_position->aliasID = 1;
	KBVar* pRole_position_defval = new KBVar(FVector());
	pRole_position->pDefaultVal = pRole_position_defval;
	pRoleModule->propertys.Add(TEXT("position"), pRole_position); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_position->aliasID, pRole_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(position / 40000).");

	Property* pRole_direction = new Property();
	pRole_direction->name = TEXT("direction");
	pRole_direction->properUtype = 40001;
	pRole_direction->properFlags = 4;
	pRole_direction->aliasID = 2;
	KBVar* pRole_direction_defval = new KBVar(FVector());
	pRole_direction->pDefaultVal = pRole_direction_defval;
	pRoleModule->propertys.Add(TEXT("direction"), pRole_direction); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_direction->aliasID, pRole_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(direction / 40001).");

	Property* pRole_spaceID = new Property();
	pRole_spaceID->name = TEXT("spaceID");
	pRole_spaceID->properUtype = 40002;
	pRole_spaceID->properFlags = 16;
	pRole_spaceID->aliasID = 3;
	KBVar* pRole_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pRole_spaceID->pDefaultVal = pRole_spaceID_defval;
	pRoleModule->propertys.Add(TEXT("spaceID"), pRole_spaceID); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_spaceID->aliasID, pRole_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(spaceID / 40002).");

	Property* pRole_Name = new Property();
	pRole_Name->name = TEXT("Name");
	pRole_Name->properUtype = 5;
	pRole_Name->properFlags = 4;
	pRole_Name->aliasID = 4;
	KBVar* pRole_Name_defval = new KBVar(FString());
	pRole_Name->pDefaultVal = pRole_Name_defval;
	pRoleModule->propertys.Add(TEXT("Name"), pRole_Name); 

	pRoleModule->usePropertyDescrAlias = true;
	pRoleModule->idpropertys.Add((uint16)pRole_Name->aliasID, pRole_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(Role), property(Name / 5).");

	pRoleModule->useMethodDescrAlias = true;
}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("BOOL");
		FString name = TEXT("UINT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 3;
		FString typeName = TEXT("UINT16");
		FString name = TEXT("UINT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 5;
		FString typeName = TEXT("DBID");
		FString name = TEXT("UINT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 4;
		FString typeName = TEXT("UINT32");
		FString name = TEXT("UINT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 6;
		FString typeName = TEXT("INT8");
		FString name = TEXT("INT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 7;
		FString typeName = TEXT("INT16");
		FString name = TEXT("INT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 8;
		FString typeName = TEXT("ENTITY_ID");
		FString name = TEXT("INT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 9;
		FString typeName = TEXT("INT64");
		FString name = TEXT("INT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 1;
		FString typeName = TEXT("STRING");
		FString name = TEXT("STRING");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 12;
		FString typeName = TEXT("UNICODE");
		FString name = TEXT("UNICODE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 13;
		FString typeName = TEXT("FLOAT");
		FString name = TEXT("FLOAT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 14;
		FString typeName = TEXT("DOUBLE");
		FString name = TEXT("DOUBLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PYTHON");
		FString name = TEXT("PYTHON");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_DICT");
		FString name = TEXT("PY_DICT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_TUPLE");
		FString name = TEXT("PY_TUPLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_LIST");
		FString name = TEXT("PY_LIST");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 20;
		FString typeName = TEXT("ENTITYCALL");
		FString name = TEXT("ENTITYCALL");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 11;
		FString typeName = TEXT("BLOB");
		FString name = TEXT("BLOB");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 15;
		FString typeName = TEXT("VECTOR2");
		FString name = TEXT("VECTOR2");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 16;
		FString typeName = TEXT("VECTOR3");
		FString name = TEXT("VECTOR3");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 17;
		FString typeName = TEXT("VECTOR4");
		FString name = TEXT("VECTOR4");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 22;
		FString typeName = TEXT("ENTITY_LIST");
		DATATYPE_ENTITY_LIST* pDatatype = new DATATYPE_ENTITY_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 23;
		FString typeName = TEXT("ROLE_INFO");
		DATATYPE_ROLE_INFO* pDatatype = new DATATYPE_ROLE_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 24;
		FString typeName = TEXT("ROLE_LIST");
		DATATYPE_ROLE_LIST* pDatatype = new DATATYPE_ROLE_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 26;
		FString typeName = TEXT("ROOM_INFO");
		DATATYPE_ROOM_INFO* pDatatype = new DATATYPE_ROOM_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 27;
		FString typeName = TEXT("ROOM_LIST");
		DATATYPE_ROOM_LIST* pDatatype = new DATATYPE_ROOM_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	for(auto& Elem : EntityDef::datatypes)
	{
		if(Elem.Value)
		{
			Elem.Value->bind();
		}
	}
}


}