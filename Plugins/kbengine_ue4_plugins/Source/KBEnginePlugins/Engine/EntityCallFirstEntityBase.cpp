#include "EntityCallFirstEntityBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_FirstEntityBase::EntityBaseEntityCall_FirstEntityBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_FirstEntityBase::~EntityBaseEntityCall_FirstEntityBase()
{
}

void EntityBaseEntityCall_FirstEntityBase::ReqRoleList()
{
	Bundle* pBundleRet = newCall("ReqRoleList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_FirstEntityBase::ReqRoomList()
{
	Bundle* pBundleRet = newCall("ReqRoomList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_FirstEntityBase::ReqSelectRole(uint64 arg1)
{
	Bundle* pBundleRet = newCall("ReqSelectRole", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_FirstEntityBase::SelectRoom(uint64 arg1)
{
	Bundle* pBundleRet = newCall("SelectRoom", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}



EntityCellEntityCall_FirstEntityBase::EntityCellEntityCall_FirstEntityBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_FirstEntityBase::~EntityCellEntityCall_FirstEntityBase()
{
}

void EntityCellEntityCall_FirstEntityBase::say(const FString& arg1)
{
	Bundle* pBundleRet = newCall("say", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}


}