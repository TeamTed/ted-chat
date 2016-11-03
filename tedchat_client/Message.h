/*
 * Message.h
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "Types.h" 
#include "Contact.h"

class Message {

	public:
		
	Message(const SenderContact &sender,
			const Contact &receiver,
			const Plaintext &plaintext) : 
	m_sender(sender), m_receiver(receiver), m_plaintext(plaintext){
		
	}

	Plaintext getPlaintext() const{
		return m_plaintext;
	}
	
	Contact getReceiver() const{
		return m_receiver;
	}

private:
	SenderContact	m_sender;
	Contact			m_receiver;
	Plaintext		m_plaintext;
};

#endif /* MESSAGE_H */
