/*
 * main.cpp
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "Server.h"

#include <iostream>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include "boost/algorithm/string.hpp"

SenderContact register_new_user_submenu(Server &server);

//why is (SenderContact) `me` not const?  Because they may attempt to 
//use authenticate, which is non-const
void get_messages_submenu(Server &server, SenderContact &me);
void send_message_submenu(Server &server, SenderContact &me);
void create_new_contact_submenu(Server &server, SenderContact &me);

//look for contacts in the cwd and ask with a menu
Contact pick_contact_from_submenu();

int main(int argc, char *argv[])
{

	pick_contact_from_submenu();

	Server server;
	
	//create sender contact

	char input = 0;
	while(input != '1' && input != '2'){
		std::cout << "1. login" << std::endl;
		std::cout << "2. register new" << std::endl;
		std::cin >> input;
	}
	std::string username = "cknapp";
	std::string password = "tedchat00";

	std::cout << "username: " << std::endl;
	std::cin >> username;
	std::cout << "password: " << std::endl;
	std::cin >> password;

	SenderContact me(username);
	me.setPassword(password);

	if( input == '2' ){
		me = register_new_user_submenu(server);
	}

	server.authenticate(me);
	

	while(true){
		std::cout << "1. get messages" << std::endl;
		std::cout << "2. send message" << std::endl;
		std::cout << "3. create new contact" << std::endl;
		
		char input;
		std::cin >> input;

		if(input == '1'){
			get_messages_submenu(server, me);
		} else if(input == '2'){
			//send a message
			send_message_submenu(server, me);			
		} else {
			return 0;
		}
	}
	return 0;
}

SenderContact register_new_user_submenu(Server &server){

	std::string username;
	std::string password;

	std::cout << "username: " << std::endl;
	std::cin >> username;
	std::cout << "password: " << std::endl;
	std::cin >> password;

	SenderContact me(username);
	me.setPassword(password);

	server.register_user(me);

	return me;
}

void get_messages_submenu(Server &server, SenderContact &me){
	MessageSet messages = server.get_messages(me);
	std::cout << "==================================" << std::endl;	
	for (auto &i : messages) {
		std::cout << "from:  " << i.getReceiverUsername() << std::endl;
		std::cout << "----------------------------------" << std::endl;
		std::cout << "msg:" << i.getPlaintext() << std::endl;
		std::cout << "==================================" << std::endl;
	}

}

void send_message_submenu(Server &server, SenderContact &me){
	std::string recipient_username;
	std::string message_text;

	std::cout << "Recipient username: " << std::endl;
	std::cin >> recipient_username;
	std::cout << "message text: " << std::endl;
	std::cin >> message_text;

	OutgoingMessage my_message( me, recipient_username, message_text);
	server.send(me, my_message);
}

void create_new_contact_submenu(Server &server, const SenderContact &me){
	
	
}

void search_directory_for_contacts(std::vector<std::string> &contact_name_vec) {
	//get a list of files in the current working directory with the
	//naming convention <username>.publickey
	
	boost::filesystem::path wd = boost::filesystem::current_path();

    boost::filesystem::directory_iterator end_iter;
    for ( boost::filesystem::directory_iterator dir_itr( wd );
          dir_itr != end_iter;
          ++dir_itr ) {
		try {
			if ( boost::filesystem::is_regular_file( dir_itr->status() ) ){
				std::string name_str = dir_itr->path().filename().native();

				std::vector<std::string> split_str;
				boost::split(split_str, name_str, boost::is_any_of("."));
				if(split_str.size() == 2){
					//a candidate!!!
					if(split_str[1] == "privatekey"){
						contact_name_vec.push_back(split_str[0]);
					}
				}
			}
		}
		catch ( const std::exception & ex )
		{
			std::cout << dir_itr->path().filename()
				<< " " << ex.what() << std::endl;
		}
	}
}

Contact pick_contact_from_submenu(){
	//get a list of usernames in the current working directory
	std::vector<std::string> contact_name_vec;

	search_directory_for_contacts(contact_name_vec);
	for (int i = 0; i < contact_name_vec.size(); ++i) {
		std::cout << i << "\t" << contact_name_vec[i] << std::endl;
	}

	return Contact();
}
