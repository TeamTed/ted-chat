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
				{"password", new_user.getPassword()  },
				{"email", "knapp.cory@gmail.com"}	}
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
		auto token = response.find("jwt");
		if(token == response.end()){
			std::cout << "error, no jwt provided";
			return;
		}
		user.setJWT(*token);
}

//sender is not const, because it may attempt to reauthenticate which calls a
//non-const function.
void Server::send(SenderContact &sender, const OutgoingMessage &message){
	while(true){
		std::cout << "while(true){" << std::endl;

	auto response = get_json_for(
						c_server_url + "post",
						{
							{"jwt", sender.getJWT() },
							{"text", (std::string)message.getPlaintext() },
							{"receiver", message.getReceiverUsername() }
						}
					);
		auto error = response.find("error");
		if(error == response.end()){
			std::cout << "message sent" << std::endl;
			return;
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
				return;
			}
		}
	}
}

MessageSet Server::get_messages(SenderContact &sender){
	auto response = get_json_for(
						c_server_url + "get",
						{
							{"jwt", sender.getJWT() },						
						}
					);
		auto error = response.find("error");
		if(error == response.end()){
			//std::cout << "retrieved" << std::endl;
		} else {
			//error reported
			if( *error == "jwt expired"){
				//try to get a new token.
				authenticate(sender);
				//end try again
			} else {
				//some other error happened from which we can not easily recover
				std::cout << "error getting message: " <<
					*error << std::endl;
			}
		}
		
		auto json_messages = response.find("messages");
		MessageSet return_vec;
		for (auto &e : *json_messages) {

			std::string sender_field = e["sender"];
			std::string receiver_field = e["receiver"];
			std::string text_field = e["text"];
			//TODO error check for missing fields


			IncomingMessage new_message(
				sender_field,
				receiver_field,
				text_field
				);

			return_vec.push_back(new_message);
		}
	return return_vec;
}
