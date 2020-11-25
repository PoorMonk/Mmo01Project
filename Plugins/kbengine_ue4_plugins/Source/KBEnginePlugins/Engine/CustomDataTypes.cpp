#include "CustomDataTypes.h"
#include "EntityDef.h"
#include "KBDebug.h"
#include "DataTypes.h"
#include "Runtime/Core/Public/Misc/Variant.h"

namespace KBEngine
{

void DATATYPE_ENTITY_LIST::createFromStreamEx(MemoryStream& stream, ENTITY_LIST& datas)
{
	uint32 size = stream.readUint32();
	while(size > 0)
	{
		--size;
		datas.Add(stream.readInt32());
	};

}

void DATATYPE_ENTITY_LIST::addToStreamEx(Bundle& stream, const ENTITY_LIST& v)
{
	stream.writeUint32((uint32)v.Num());
	for(int i=0; i<v.Num(); ++i)
	{
		stream.writeInt32(v[i]);
	};
}

void DATATYPE_ROLE_INFO::createFromStreamEx(MemoryStream& stream, ROLE_INFO& datas)
{
	datas.Dbid = stream.readUint64();
	datas.Name = stream.readUnicode();
}

void DATATYPE_ROLE_INFO::addToStreamEx(Bundle& stream, const ROLE_INFO& v)
{
	stream.writeUint64(v.Dbid);
	stream.writeUnicode(v.Name);
}

void DATATYPE_ROLE_LIST::createFromStreamEx(MemoryStream& stream, ROLE_LIST& datas)
{
	Value_DataType.createFromStreamEx(stream, datas.Value);
}

void DATATYPE_ROLE_LIST::addToStreamEx(Bundle& stream, const ROLE_LIST& v)
{
	Value_DataType.addToStreamEx(stream, v.Value);
}

void DATATYPE_ROOM_INFO::createFromStreamEx(MemoryStream& stream, ROOM_INFO& datas)
{
	datas.RoomId = stream.readUint64();
	datas.Name = stream.readUnicode();
}

void DATATYPE_ROOM_INFO::addToStreamEx(Bundle& stream, const ROOM_INFO& v)
{
	stream.writeUint64(v.RoomId);
	stream.writeUnicode(v.Name);
}

void DATATYPE_ROOM_LIST::createFromStreamEx(MemoryStream& stream, ROOM_LIST& datas)
{
	Value_DataType.createFromStreamEx(stream, datas.Value);
}

void DATATYPE_ROOM_LIST::addToStreamEx(Bundle& stream, const ROOM_LIST& v)
{
	Value_DataType.addToStreamEx(stream, v.Value);
}


}