/*
 * Message.h
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "Types.h" 
#include "Contact.h"

#include <iostream>

class OutgoingMessage {

	public:
		
	OutgoingMessage(const SenderContact &sender_username,
			const std::string receiver_username,
			const std::string plaintext) : 
	m_sender(sender_username),
	m_receiver(receiver_username),
	m_plaintext(plaintext){
		
	}

	Plaintext getPlaintext() const{
		return m_plaintext;
	}
	
	std::string getReceiverUsername() const{
		return m_receiver;
	}

private:
	SenderContact	m_sender;
	std::string m_receiver;
	Plaintext m_plaintext;
};

class IncomingMessage {

	public:
		
	IncomingMessage(const std::string sender_username,
			const std::string receiver_username,
			const std::string plaintext) : 
	m_sender(sender_username),
	m_receiver(receiver_username),
	m_plaintext(plaintext){
	}

	std::string getPlaintext() const{
		return m_plaintext;
	}
	
	std::string getReceiverUsername() const{
		return m_receiver;
	}

private:
	std::string	m_sender;
	std::string	m_receiver;
	std::string	m_plaintext;
};


#endif /* MESSAGE_H */
