/*
 * Main.cpp
 *
 *  Created on: 24 mai 2014
 *      Author: gguigue
 */

#include "PGConnection.h"
#include "Entity_test.h"


int main() {
	WS_PERSISTENCE::PGConnection toto;
	WS_PERSISTENCE::CEntityDBDescriptorTests t1;
	t1.testRequestCreation();
	return 0;

}

