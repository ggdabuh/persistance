/*
 * Entity.cpp
 *
 *  Created on: 14/05/2014
 *      Author: juan
 */

#include "Entity.hpp"
#include "PGConnection.h"
#include <stdint.h>
#include <sstream>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>
#include <cstring>


namespace WS_PERSISTENCE {

map<int, size_t> CEntityDBDescriptor::_typeInfo;


CEntity::CEntity(CDBConnection* conn) : _dbConnection(conn) {
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

const string& CEntityDBDescriptor::getRequestId(PGconn * conn) {
	static unsigned int index = 1;
	const size_t buffer_size = 40;

	if(req_id.empty()) {
		char tmp[buffer_size];
		snprintf(tmp, buffer_size,"PERS%u", index++);
		PGresult * res = PQprepare(conn,
		                    tmp,
		                    createRequest().c_str(),
		                    _keys.size(),
		                    NULL);
		switch(PQresultStatus(res)) {
		case PGRES_COMMAND_OK:
			break;
		default:
			PQclear(res);
			throw std::runtime_error("PQprepare failed");
		}
		req_id = tmp;

		PQclear(res);
	}
	return req_id;

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

void CEntity::GenerateBeanData(CEntityDBDescriptor* entityDBDescriptor,
		CDBConnection* dbConnection) {
	PGconn* conn = dynamic_cast<PGConnection&>(*dbConnection).connection();
	const string& id = entityDBDescriptor->getRequestId(conn);

	vector<char const*> values;
	vector<int> paramLength, paramFormat;
	vector<S_Field_Description>::const_iterator begin = entityDBDescriptor->_keys.begin(),
												end = entityDBDescriptor->_keys.end();

	for(int i = 0;begin!=end;++begin,++i) {
		if(begin->_fileType == VAR_CHAR) {

			values.push_back(((string*)_BeanId.at(i))->c_str());
			paramLength.push_back(CEntityDBDescriptor::_typeInfo[begin->_fileType]);
			paramFormat.push_back(0);
		} else {
			values.push_back((char*)_BeanId.at(i));
			paramLength.push_back(CEntityDBDescriptor::_typeInfo[begin->_fileType]);
			paramFormat.push_back(1);
		}

	}

	PGresult * res = PQexecPrepared(conn,
	                         id.c_str(),
	                         entityDBDescriptor->_keys.size(),
	                         values.data(),
	                         paramLength.data(),
	                         paramFormat.data(),
	                         1);

	switch(PQresultStatus(res)) {
	case PGRES_COMMAND_OK:
		break;
	default:
		PQclear(res);
		throw std::runtime_error("PQpexec failed");
	}

	for(unsigned int i=0;i<entityDBDescriptor->_fields.size();++i) {
		char * ptr = PQgetvalue(res,
		                 0,
		                 i);

		void* copy = malloc(CEntityDBDescriptor::_typeInfo[entityDBDescriptor->_fields.at(i)._fileType]);
		if(entityDBDescriptor->_fields.at(i)._fileType == VAR_CHAR) {
			string* str = new(copy) string(ptr);
			_BeanData.push_back(str);
		} else {
			memcpy(copy, ptr,CEntityDBDescriptor::_typeInfo[entityDBDescriptor->_fields.at(i)._fileType]);
			_BeanData.push_back(copy);
		}

	}
	PQclear(res);

}

} /* namespace WS_PERSISTENCE */
/******************************************************************************/
