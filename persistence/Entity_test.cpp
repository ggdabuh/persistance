/*
 * Entity_test.cpp
 *
 *  Created on: 14/05/2014
 *      Author: juan
 */
#include "Entity.hpp"
#include "Entity_test.h"

#include <iostream>

namespace WS_PERSISTENCE {


void CEntityDBDescriptorTests::testRequestCreation() {
	 CEntityDBDescriptor test;
	 test.AddField("toto", CHARACTER);
	 test.AddField("tata", CHARACTER);
	 test.AddField("tutu", INTEGER);

	 test.SetTable("BIDULE");

	 test.AddKey("titi", VAR_CHAR);
	 test.AddKey("tyty", VAR_CHAR);

	 std::cout << test.createRequest();
}

} /* namespace WS_PERSISTENCE */
