/*
 * Server.h
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SERVER_H
#define SERVER_H

typedef std::vector<Message> MessageSet;


class Server
{
public:
	Server();
	virtual ~Server ();

	void send(const Message &message);
	void getMessages(SenderContact &);


private:
	/* data */
};

#endif /* !SERVER_H */
