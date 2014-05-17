/*
 * DBConnectionException.cpp
 *
 *  Created on: 16 mai 2014
 *      Author: Guillaume
 */

#include "DBConnectionException.h"

namespace WS_PERSISTENCE {

DBConnectionException::DBConnectionException(char const * const message) : message(message) {
	// TODO Auto-generated constructor stub

}

DBConnectionException::~DBConnectionException() {
	// TODO Auto-generated destructor stub
}

} /* namespace WS_PERSISTENCE */

const char* WS_PERSISTENCE::DBConnectionException::what() const throw () {
	return message.c_str();
}
