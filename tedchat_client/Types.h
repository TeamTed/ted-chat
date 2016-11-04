/*
 * 
 * Distributed under terms of the MIT license.
 */

#ifndef TYPES_H
#define TYPES_H

#include <string>

// create a subclass of std::string for type safety
class Plaintext : public std::string{
	public:
	Plaintext(){
	}

	Plaintext(const std::string &k){
		*this = k;
	}

};

// create a subclass of std::string for type safety
class Ciphertext: public std::string{
	public:
	Ciphertext(){
	}

	Ciphertext(const std::string &k){
		*this = k;
	}
};

// create a subclass of std::string for type safety
class Key: public std::string{
	public:
	Key(){
	}

	Key(const std::string &k){
		*this = k;
	}
};

// create a subclass of std::string for type safety
class PublicKey: public Key{
	public:
	PublicKey(){
	}

	PublicKey(const Key &k){
		*this = k;
	}
};

// create a subclass of std::string for type safety
class PrivateKey: public Key{
	public:
	PrivateKey(){
	}

	PrivateKey(const Key &k){
		*this = k;
	}
};

#endif /* !TYPES_H */
