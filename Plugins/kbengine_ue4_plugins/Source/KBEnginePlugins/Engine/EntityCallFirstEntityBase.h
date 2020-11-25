/*
	Generated by KBEngine!
	Please do not modify this file!
	
	tools = kbcmd
*/

#pragma once

#include "KBECommon.h"
#include "EntityCall.h"
#include "KBETypes.h"
#include "CustomDataTypes.h"


// defined in */scripts/entity_defs/FirstEntity.def

namespace KBEngine
{

class KBENGINEPLUGINS_API EntityBaseEntityCall_FirstEntityBase : public EntityCall
{
public:

	EntityBaseEntityCall_FirstEntityBase(int32 eid, const FString& ename);

	virtual ~EntityBaseEntityCall_FirstEntityBase();
	void ReqRoleList();
	void ReqRoomList();
	void ReqSelectRole(uint64 arg1);
	void SelectRoom(uint64 arg1);
};

class KBENGINEPLUGINS_API EntityCellEntityCall_FirstEntityBase : public EntityCall
{
public:

	EntityCellEntityCall_FirstEntityBase(int32 eid, const FString& ename);

	virtual ~EntityCellEntityCall_FirstEntityBase();
	void say(const FString& arg1);
};

}