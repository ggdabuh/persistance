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

}


int CEntityDBDescriptor::Initialize(void)
{
	CEntityDBDescriptor::LoadTypes();

	return 0;
}

void CEntityDBDescriptor::AddField(string _fieldName, int _fileType) {
	S_Field_Description* desc = new S_Field_Description();
	*desc = {(int)_fields.size(), _fieldName,_fileType };
	_fields.push_back(desc);
}

void CEntityDBDescriptor::SetTable(const string& _tableName) {
	_table = _tableName;
}

CEntityDBDescriptor::~CEntityDBDescriptor() {
	for(vector<S_Field_Description* >::iterator begin = _fields.begin(), end = _fields.end();
			begin != end;
			++begin) {
		delete *begin;
	}
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
