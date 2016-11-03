/*
 * Server.cpp
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "Server.h"


struct ServerResponse {
	/* data */
};

Server::Server(){

}

void Server::register_user(const SenderContact &new_user) {
	
	std::cout << get_json_for(
			c_server_url + "register",
			{
				{"username", new_user.getName() },
				{"password", new_user.getPassword()  } }
			) << std::endl;
}

void Server::authenticate(SenderContact &user){
	auto response =get_json_for(
			c_server_url + "jwt",
			{
				{"username", user.getName() },
				{"password", user.getPassword()  } }
			);
		auto error = response.find("error");
		if(error != response.end()){
			std::cout << "authentication error: " <<
					*error << std::endl;
		}
}

void Server::send(SenderContact &sender, const Message &message){
	while(true){
	auto response = get_json_for(
						c_server_url + "post",
						{
							{"jwt", sender.getJWT() },
							{"text", message.getPlaintext() },
							{"receiver", message.getReceiver().getName() }
						}
					);
		auto error = response.find("error");
		if(error == response.end()){
			std::cout << "message sent" << std::endl;
		} else {
			//error reported
			if( *error == "jwt expired"){
				//try to get a new token.
				authenticate(sender);
				//end try again
			} else {
				//some other error happened from which we can not easily recover
				std::cout << "error sending message: " <<
					*error << std::endl;
			}
		}
	}
}
