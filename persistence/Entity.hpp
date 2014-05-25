/*
 * Entity.hpp
 *
 *  Created on: 14/05/2014
 *      Author: juan
 */


#include <stdint.h>


#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <string>
#include <libpq-fe.h>

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
	friend class CEntityDBDescriptorTests;
	friend class CEntity;

	public:

		CEntityDBDescriptor();

		virtual ~CEntityDBDescriptor();

		void AddField(string _fieldName, int _fileType);

		void AddKey(string _fieldName, int _fileType);

		void SetTable(const string& _tableName);

		const string& getRequestId(PGconn *);

	private:

		string createRequest();

		string _table, req_id;

		vector<S_Field_Description> _fields, _keys;

		static int Initialize(void);
		static int LoadTypes(void);

		static map<int, size_t> _typeInfo;

};

////////////////////////////////////////////////////////////////////////////////
class CEntity {

	public:

		CEntity(CDBConnection*);
		virtual ~CEntity();

		static vector<CEntity*>* SerializeEntities(CFilter* filter);

		void GenerateBeanData(CEntityDBDescriptor* entityDBDescriptor,
							CDBConnection* dbConnection);

	protected:

		int ReLoadFromDB(void);
		int UpdateDB(void);

	private:

		// map -> field_id, field_value
		vector<void*> _BeanData;

		vector<void*> _BeanId;

		CEntityDBDescriptor* _entityDBDescriptor;
		CDBConnection* _dbConnection;

		int64_t _entity_id;
};

} /* namespace WS_PERSISTENCE */

/******************************************************************************/
#endif /* ENTITY_HPP_ */
