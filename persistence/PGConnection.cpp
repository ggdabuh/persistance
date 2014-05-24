/*
 * PGConnection.cpp
 *
 *  Created on: 15 mai 2014
 *      Author: Guillaume
 */

#include "PGConnection.h"
#include <stdexcept>
#include "DBConnectionException.h"
#include <libpq-fe.h>


namespace WS_PERSISTENCE {

PGConnection::PGConnection() {
	// TODO Auto-generated constructor stub
	char const * const  keywords[] = {/*"host",*/     "dbname" , /*"port",*/"user"  , "password", NULL };
	char const * const  vals[] =     {/*"localhost",*/"mydb"   ,/*"5432",*/ "dbuser", "toto", NULL };

	conn = PQconnectdbParams(keywords, vals, 0);

	try {
		switch(PQstatus(conn)) {
		case CONNECTION_OK:
			break;

		case CONNECTION_BAD:
			throw DBConnectionException(PQerrorMessage(conn));

		default:
			throw std::runtime_error("Connection failure: unexpected connection status");
		}
	} catch (...) {
		PQfinish(conn);
		throw;
	}

}

PGConnection::~PGConnection() {
	PQfinish(conn);

}

} /* namespace WS_PERSISTENCE */
