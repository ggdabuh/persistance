/*
 * Entity.cpp
 *
 *  Created on: 14/05/2014
 *      Author: juan
 */

#include "Entity.hpp"
#include <stdint.h>
#include <sstream>

namespace WS_PERSISTENCE {

map<int, size_t> CEntityDBDescriptor::_typeInfo;


CEntity::CEntity() {
	// TODO Auto-generated constructor stub

}

CEntity::~CEntity() {

}

CEntityDBDescriptor::CEntityDBDescriptor() {

}


int CEntityDBDescriptor::Initialize(void)
{
	CEntityDBDescriptor::LoadTypes();

	return 0;
}

void CEntityDBDescriptor::AddField(string _fieldName, int _fileType) {
	S_Field_Description desc = {(int)_fields.size(), _fieldName,_fileType };
	_fields.push_back(desc);
}

void CEntityDBDescriptor::AddKey(string _fieldName, int _fileType) {
	S_Field_Description desc = {(int)_keys.size(), _fieldName,_fileType };
	_keys.push_back(desc);
}

void CEntityDBDescriptor::SetTable(const string& _tableName) {
	_table = _tableName;
}

CEntityDBDescriptor::~CEntityDBDescriptor() {

}

string CEntityDBDescriptor::createRequest() {

	//static unsigned int req_id = 0;
	ostringstream ss;
	if(_fields.empty()) {
		throw "_fields.empty()";
	}
	if(_keys.empty()) {
		throw "_keys.empty()";
	}
	if(_table.empty()) {
		throw "_table.empty()";
	}
	vector<S_Field_Description>::const_iterator begin = _fields.begin(), end=_fields.end();
	ss << "SELECT "
			<< begin->_fieldName;
	for(++begin; begin != end; ++begin) {
		ss << ", " << begin->_fieldName;
	}
	ss << " FROM " << _table << " WHERE ";
	int paramNb = 1;
	begin = _keys.begin(), end=_keys.end();
	ss << begin->_fieldName << " = $" << paramNb++;
	for(++begin; begin != end; ++begin) {
		ss << " AND " << begin->_fieldName << " = $" << paramNb++;
	}

	return ss.str();

}

const string& CEntityDBDescriptor::getRequestId() {

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
