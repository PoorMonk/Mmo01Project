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


// defined in */scripts/entity_defs/SRoom.def

namespace KBEngine
{

class KBENGINEPLUGINS_API EntityBaseEntityCall_SRoomBase : public EntityCall
{
public:

	EntityBaseEntityCall_SRoomBase(int32 eid, const FString& ename);

	virtual ~EntityBaseEntityCall_SRoomBase();
};

class KBENGINEPLUGINS_API EntityCellEntityCall_SRoomBase : public EntityCall
{
public:

	EntityCellEntityCall_SRoomBase(int32 eid, const FString& ename);

	virtual ~EntityCellEntityCall_SRoomBase();
};

}