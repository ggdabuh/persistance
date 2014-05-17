/*
 * DBexception.h
 *
 *  Created on: 16 mai 2014
 *      Author: Guillaume
 */

#ifndef DBEXCEPTION_H_
#define DBEXCEPTION_H_

#include <exception>

namespace WS_PERSISTENCE {

class DBexception: public std::exception {
public:
	DBexception();
	virtual ~DBexception() throw ();

};

} /* namespace WS_PERSISTENCE */

#endif /* DBEXCEPTION_H_ */
