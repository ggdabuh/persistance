/*
 * DBConnectionException.h
 *
 *  Created on: 16 mai 2014
 *      Author: Guillaume
 */

#ifndef DBCONNECTIONEXCEPTION_H_
#define DBCONNECTIONEXCEPTION_H_

#include "DBexception.h"

namespace WS_PERSISTENCE {

class DBConnectionException: public WS_PERSISTENCE::DBexception {
public:
	DBConnectionException(char const * const message);
	virtual ~DBConnectionException();

	virtual const char* what() const throw();

private:
	std::string message;
};

} /* namespace WS_PERSISTENCE */

#endif /* DBCONNECTIONEXCEPTION_H_ */
