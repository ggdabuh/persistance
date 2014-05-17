/*
 * Entity.hpp
 *
 *  Created on: 14/05/2014
 *      Author: juan
 */

#ifdef WIN32
#include <stdint.h>
#else
#include < >
#endif

#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "DBConnection.h"

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

using namespace std;

namespace WS_PERSISTENCE {


////////////////////////////////////////////////////////////////////////////////
enum E_FIELD_TYPES
{
	CHARACTER = 	0x0000,
	INTEGER =		0x0001,
	BOOLEAN =		0x0002,
	VAR_CHAR =		0x0003,
	BIGINT = 		0x0004,
	SMALLINT =		0x0005

	/*
	 * TODO: Other types. Postgresql types style.
	 *
	 */
};

////////////////////////////////////////////////////////////////////////////////
struct S_Field_Description
{
	int _field_id;
	string _fieldName;
	int _fileType;
};

////////////////////////////////////////////////////////////////////////////////
class CQueryGenerator
{



};

////////////////////////////////////////////////////////////////////////////////
class CFilter
{

};

////////////////////////////////////////////////////////////////////////////////
class CEntityDBDescriptor
{
	public:

		CEntityDBDescriptor();

		virtual ~CEntityDBDescriptor();

		void AddField(string _fieldName, int _fileType);

		void SetTable(const string& _tableName);

	private:

		string _table;

		vector<S_Field_Description* > _fields;

		static int Initialize(void);
		static int LoadTypes(void);

		static map<int, size_t> _typeInfo;

};

////////////////////////////////////////////////////////////////////////////////
class CEntity {

	public:

		CEntity();
		virtual ~CEntity();

		static vector<CEntity*>* SerializeEntities(CFilter* filter);

		int GenerateBeanData(CEntityDBDescriptor* entityDBDescriptor,
							CDBConnection* dbConnection);

	protected:

		int ReLoadFromDB(void);
		int UpdateDB(void);

	private:

		// map -> field_id, field_value
		map<int, void*> _BeanData;

		CEntityDBDescriptor* _entityDBDescriptor;
		CDBConnection* _dbConnection;

		int64_t _entity_id;
};

} /* namespace WS_PERSISTENCE */

/******************************************************************************/
#endif /* ENTITY_HPP_ */
