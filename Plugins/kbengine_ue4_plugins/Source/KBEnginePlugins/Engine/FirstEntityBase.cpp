#include "FirstEntityBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"
#include "EntityComponent.h"

namespace KBEngine
{



void FirstEntityBase::onComponentsEnterworld()
{
}

void FirstEntityBase::onComponentsLeaveworld()
{
}

void FirstEntityBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_FirstEntityBase(id(), className());
}

void FirstEntityBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_FirstEntityBase(id(), className());
}

void FirstEntityBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* FirstEntityBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* FirstEntityBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void FirstEntityBase::onRemoteMethodCall(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("FirstEntity");
	uint16 methodUtype = 0;
	uint16 componentPropertyUType = 0;

	if (sm->usePropertyDescrAlias)
	{
		componentPropertyUType = stream.readUint8();
	}
	else
	{
		componentPropertyUType = stream.readUint16();
	}

	if (sm->useMethodDescrAlias)
	{
		methodUtype = stream.read<uint8>();
	}
	else
	{
		methodUtype = stream.read<uint16>();
	}

	if(componentPropertyUType > 0)
	{
		KBE_ASSERT(false);

		return;
	}

	Method* pMethod = sm->idmethods[methodUtype];

	switch(pMethod->methodUtype)
	{
		case 10:
		{
			ROLE_LIST OnReqRoleList_arg1;
			((DATATYPE_ROLE_LIST*)pMethod->args[0])->createFromStreamEx(stream, OnReqRoleList_arg1);
			OnReqRoleList(OnReqRoleList_arg1);
			break;
		}
		case 8:
		{
			ROOM_LIST OnReqRoomList_arg1;
			((DATATYPE_ROOM_LIST*)pMethod->args[0])->createFromStreamEx(stream, OnReqRoomList_arg1);
			OnReqRoomList(OnReqRoomList_arg1);
			break;
		}
		case 11:
		{
			uint8 OnSelectRole_arg1 = stream.readUint8();
			uint64 OnSelectRole_arg2 = stream.readUint64();
			OnSelectRole(OnSelectRole_arg1, OnSelectRole_arg2);
			break;
		}
		case 9:
		{
			OnSelectRoom();
			break;
		}
		case 6:
		{
			onEnter();
			break;
		}
		case 7:
		{
			FString onSay_arg1 = stream.readUnicode();
			onSay(onSay_arg1);
			break;
		}
		default:
			break;
	};
}

void FirstEntityBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("FirstEntity");

	while(stream.length() > 0)
	{
		uint16 componentPropertyUType = 0;
		uint16 properUtype = 0;

		if (sm->usePropertyDescrAlias)
		{
			componentPropertyUType = stream.readUint8();
			properUtype = stream.read<uint8>();
		}
		else
		{
			componentPropertyUType = stream.readUint16();
			properUtype = stream.read<uint16>();
		}

		if(componentPropertyUType > 0)
		{
			KBE_ASSERT(false);

			return;
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 40001:
			{
				FVector oldval_direction = direction;
				direction = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onDirectionChanged(oldval_direction);
				}
				else
				{
					if(inWorld())
						onDirectionChanged(oldval_direction);
				}

				break;
			}
			case 40000:
			{
				FVector oldval_position = position;
				position = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onPositionChanged(oldval_position);
				}
				else
				{
					if(inWorld())
						onPositionChanged(oldval_position);
				}

				break;
			}
			case 40002:
			{
				stream.readUint32();
				break;
			}
			default:
				break;
		};
	}
}

void FirstEntityBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["FirstEntity"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	FVector oldval_direction = direction;
	Property* pProp_direction = pdatas[2];
	if(pProp_direction->isBase())
	{
		if(inited() && !inWorld())
			onDirectionChanged(oldval_direction);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_direction->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDirectionChanged(oldval_direction);
			}
		}
	}

	FVector oldval_position = position;
	Property* pProp_position = pdatas[1];
	if(pProp_position->isBase())
	{
		if(inited() && !inWorld())
			onPositionChanged(oldval_position);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_position->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onPositionChanged(oldval_position);
			}
		}
	}

}

FirstEntityBase::FirstEntityBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL)
{
}

FirstEntityBase::~FirstEntityBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void FirstEntityBase::attachComponents()
{
}

void FirstEntityBase::detachComponents()
{
}

}