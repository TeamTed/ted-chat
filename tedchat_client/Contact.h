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

#include "json.hpp"

#include "Types.h" 



class Contact{
public:

	//keep track of the last datetime i got a message from this contact XXX

	Contact(){ //XXX take this out at some point
	}

	//construct a Contact from a json object
	Contact(nlohmann::json j){
		assert(j.is_object());

		//set the username element;
		auto username = j.find("username");
		if (username != j.end()) {
			setName(*username);			
		} else {
			std::cout << "no username found in contact. \n" <<
				j;
			assert(false);
		}

		//set the public key
		auto publickey = j.find("publickey");
		if (publickey != j.end()) {
			setPublicKey(*publickey);			
		} else {
			std::cout << "no publickey found in contact. \n" <<
				j;
			assert(false);
		}

		//set the session key
		auto sessionkey = j.find("sessionkey");
		if (sessionkey != j.end()) {
			setSessionPublicKey(*sessionkey);			
		} // no else, it's fine to not have a sessionkey, right? XXX
	}

	nlohmann::json to_json(){
		nlohmann::json j;
		j["username"] = getName();
		j["publickey"] = getPublicKey();
		j["sessionkey"] = getSessionPublicKey();
		//TODO save message history

		return j;
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
	
	//called after I send a message if renegotiation conditions are met
	void renegotiate_temp_key();

private:
	std::string m_name;
	PublicKey m_publickey;

	//Renegotiated
	//Updated on each receive 
	PublicKey m_temp_pk;

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
