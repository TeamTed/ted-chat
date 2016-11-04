/*
 * main.cpp
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "Server.h"

#include <iostream>

int main(int argc, char *argv[])
{
	Server server;
	
	//create sender contact
	SenderContact me;

	char input = 0;
	/* while(input != '1' && input != '2'){ */
	/* 	std::cout << "1. login" << std::endl; */
	/* 	std::cout << "2. register new" << std::endl; */
	/* 	std::cin >> input; */
	/* } */
	std::string username = "cknapp";
	std::string password = "tedchat00";

	/* std::cout << "username: " << std::endl; */
	/* std::cin >> username; */
	/* std::cout << "password: " << std::endl; */
	/* std::cin >> password; */

	me.setName(username);
	me.setPassword(password);

	if( input == '2' ){
		server.register_user(me);
	}

	server.authenticate(me);
	

	while(true){
		std::cout << "1. get messages" << std::endl;
		std::cout << "2. send messages" << std::endl;
		
		char input;
		std::cin >> input;

		if(input == '1'){
			server.get_messages(me);
		} else if(input == '2'){
			//send a message
				
		} else {
			return 0;
		}
	}
	return 0;
}
