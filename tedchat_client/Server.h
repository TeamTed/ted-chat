/*
 * Server.h
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "Message.h"
#include "Contact.h"

#include "curl_wrapper.hpp"

typedef std::vector<IncomingMessage> MessageSet;

enum server_response{

};

class Server
{
public:
	Server();
	//virtual ~Server ();

	void register_user(const SenderContact &new_user);
	void authenticate(SenderContact &);//sender contact is not const because
									   //we cache the jwt inside.
	void send(SenderContact &sender, const OutgoingMessage &message);
	std::vector<IncomingMessage> get_messages(SenderContact &);


private:
	const std::string c_server_url = "https://www.tedchat.online/tedchat/";
};

#endif /* !SERVER_H */
