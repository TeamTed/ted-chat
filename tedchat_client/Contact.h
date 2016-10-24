/*
 * Contact.h
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CONTACT_H
#define CONTACT_H

#pragma once Types.h 

class Contact{
public:
	Contact();
	Contact(const std::string &name, const PublicKey &key);
	virtual ~ ();

	std::string getName();
	void setName(const std::string &name);

	PublicKey getPublicKey();
	void setPublicKey(const PublicKey &key);

// Probably replace with function that takes secret and outputs session key
	PublicKey getSessionPublicKey();
	void setSessionPublicKey(const PublicKey &key);

private:
	std::string m_name;
	PublicKey m_publickey;

	PublicKey m_session_publickey;
};

class SenderContact : public Contact
{
public:
	SenderContact(const std::string &name,\
			const PublicKey &public_key,
			const PrivateKey &private_key);
	virtual ~Sender ();

	getPrivateKey();
	setPrivateKey(const Key &key);
	
private:
	PrivateKey m_privatekey;
};

#endif /* !CONTACT_H */
