/*
 * Entity.cpp
 *
 *  Created on: 14/05/2014
 *      Author: juan
 */

#include "Entity.hpp"

namespace WS_PERSISTENCE {

map<int, size_t> CEntityDBDescriptor::_typeInfo;


CEntity::CEntity() {
	// TODO Auto-generated constructor stub

}

CEntity::~CEntity() {
	// TODO Auto-generated destructor stub
}


int CEntityDBDescriptor::Initialize(void)
{
	CEntityDBDescriptor::LoadTypes();

	return 0;
}

void CEntityDBDescriptor::AddField(string _fieldName, int _fileType) {
	new S_Field_Description() {};
	_fields.push_back()
}

int CEntityDBDescriptor::LoadTypes(void)
{
	CEntityDBDescriptor::_typeInfo.insert(pair<int,size_t>(CHARACTER, sizeof(char)));
	CEntityDBDescriptor::_typeInfo.insert(pair<int,size_t>(INTEGER, sizeof(int)));
	CEntityDBDescriptor::_typeInfo.insert(pair<int,size_t>(BOOLEAN, sizeof(bool)));
	CEntityDBDescriptor::_typeInfo.insert(pair<int,size_t>(VAR_CHAR, sizeof(string)));
	CEntityDBDescriptor::_typeInfo.insert(pair<int,size_t>(BIGINT, sizeof(int64_t)));
	CEntityDBDescriptor::_typeInfo.insert(pair<int,size_t>(SMALLINT, sizeof(short int)));

	return 0;
}


} /* namespace WS_PERSISTENCE */
/******************************************************************************/
