/*
 * Message.h
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#pragma once Types.h 

class Message {

	Message(const SenderContact &sender,
			const Contact &receiver,
			const PlainText &plaintext){
		
	}

	

private:
	SenderContact	m_sender;
	Contact			m_receiver;
	Plaintext		m_plaintext;
}

#endif /* MESSAGE_H */
