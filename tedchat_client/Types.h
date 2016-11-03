/*
 * 
 * Distributed under terms of the MIT license.
 */

#ifndef TYPES_H
#define TYPES_H

#include <string>

// create a subclass of std::string for type safety
class Plaintext : public std::string{
};

// create a subclass of std::string for type safety
class Ciphertext: public std::string{
};

// create a subclass of std::string for type safety
class Key: public std::string{
};

// create a subclass of std::string for type safety
class PublicKey: public Key{
	public:
	PublicKey(const Key &k){
		*this = k;
	}
};

// create a subclass of std::string for type safety
class PrivateKey: public Key{
	public:
	PrivateKey(const Key &k){
		*this = k;
	}
};

#endif /* !TYPES_H */
