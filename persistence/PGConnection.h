/*
 * PGConnection.h
 *
 *  Created on: 15 mai 2014
 *      Author: Guillaume
 */

#ifndef PGCONNECTION_H_
#define PGCONNECTION_H_

#include "DBConnection.h"
#include <exception>

#include <libpq-fe.h>

namespace WS_PERSISTENCE {

struct DBError: std::exception {

};



class PGConnection: public WS_PERSISTENCE::CDBConnection {
public:
	PGConnection();
	virtual ~PGConnection();

private:
	PGConnection(const PGConnection&);
	PGconn* conn;
};

} /* namespace WS_PERSISTENCE */

#endif /* PGCONNECTION_H_ */
