/*
 * Message.h
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "Types.h" 
//#include "Contact.h"

class Message {

	public:
		
	Message(const std::string sender_username,
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
	std::string	m_sender;
	std::string	m_receiver;
	std::string	m_plaintext;
};

#endif /* MESSAGE_H */
