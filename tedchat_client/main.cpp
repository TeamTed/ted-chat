/*
 * main.cpp
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "Server.h"

#include "curl_wrapper.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	Server test;
	
	std::cout << get_json_for(
			"http://127.0.0.1:8000/tedchat/jwt",
			{ {"username", "cknapp"}, {"password","tedchat00" } }
			) << std::endl;

	return 0;
}
