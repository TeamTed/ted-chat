/*
 * Contact.h
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CONTACT_H
#define CONTACT_H

#include "Types.h" 

class Contact{
public:
	Contact();
	Contact(const std::string &name, const PublicKey &key);

	std::string getName() const{
		return m_name;
	}

	void setName(const std::string &name){
		m_name = name;
	}

	PublicKey getPublicKey() const{
		return m_publickey;
	}

	void setPublicKey(const PublicKey &key){
		m_publickey = key;
	}

	// Probably replace with function that takes secret and outputs session key
	PublicKey getSessionPublicKey() const{
		return m_session_publickey;
	}

	void setSessionPublicKey(const PublicKey &key){
		m_session_publickey = key;
	}
	
private:
	std::string m_name;
	PublicKey m_publickey;

	PublicKey m_session_publickey;
};

class SenderContact : public Contact
{
public:
	SenderContact(const std::string &name,
			const PublicKey &public_key,
			const PrivateKey &private_key);
	//virtual ~Sender ();

	PrivateKey getPrivateKey() const{
		return m_privatekey;
	}

	void setPrivateKey(const Key &key){
		m_privatekey = PrivateKey(key);
	}
	
	std::string getPassword() const{
			return m_password;
	}

	void setPassword(const std::string  &pass){
		m_password = pass;
	}

	std::string getJWT() const{
		return m_jwt;
	}

	void setJWT(const std::string  &jwt){
		m_jwt = jwt;
	}

private:
	std::string m_password;
	PrivateKey m_privatekey;
	std::string m_jwt;	
};

#endif /* !CONTACT_H */
