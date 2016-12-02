/*
 * Contact.h
 * Copyright (C) 2016 cknapp <cknapp@mbp.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "Types.h" 

class Contact{
public:
	Contact(){
	}

	Contact(const std::string &name){
		setName(name);
		std::ifstream pk_file(name+".publickey");
		if(pk_file.is_open()){
			std::stringstream buffer;
			buffer << pk_file.rdbuf();
			setPublicKey(buffer.str());
		} else {
			std::cout<<"no contact \"" + name + "\" found...\n";
			//TODO better error handling.
		}
	}

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

	SenderContact(const std::string &name) :
		Contact(name){
			std::ifstream pk_file(name+".privatekey");
		if(pk_file.is_open()){
			std::stringstream buffer;
			buffer << pk_file.rdbuf();
			setPublicKey(buffer.str());
		} else {
			std::cout<<"no contact \"" + name + "\" found...\n";
			//TODO better error handling.
		}
	}


	PrivateKey getPrivateKey() const{
		return m_privatekey;
	}

	void setPrivateKey(const PrivateKey &key){
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
