//#include "hashTable.h"
//
//unsigned int operator%(std::string s, unsigned int n) {
//	// This algorithm is based on the modular arithmetic identities
//	// (a*b)(mod n) = ((a mod n) * b)(mod n) and
//	// (a+b)(mod n) = ((a mod n) + (b mod n))(mod n)
//	// This allows this to process multiple characters at a time using longs
//	//  (at least 3 characters per modulo with n~2^16, closer to 6 characters 
//	//  for small n)
//	// Grouping the characters into blocks reduces the number of modulos 
//	//  required, marginally increasing performance since modulos are probably 
//	//  the most expensive part of this algorithm.
//	// Unfortunately, this means this operation is not constant-time, but linear 
//	//  to the length of the string. Smaller values of n will also run faster
//	//  since the "modulo crunch" is more significant for smaller bases, allowing 
//	//  more characters to fill up in between modulos.
//	// I used the 5 least significant bits because those encode the values of 
//	//  Latin letters in ASCII/Basic Latin. The 3 MSB are always 010 for
//	//  uppercase and 011 for lowercase, but since for this project we don't care
//	//  about case (and everything is in lowercase anyways), keeping the 3 MSB 
//	//  is essentially boilerplate that will make the hashing algorithm less like 
//	//  simple uniform hashing.
//	// I used the 5 LSB instead of base-26 in case we decided that special 
//	//  characters (ex. apostrophes, dashes, spaces) were important for the 
//	//  project. These values could be mapped to the empty spaces 0 or 26-31.
//	//  Also, truncating to the 5 LSB is easier to implement and probably faster 
//	//  than trying to trim it tight to base-26.
//
//	// parameters of the modulo operation
//	const int LONG_BITS = 32;   // number of bits in a long
//	const int CHAR_EXTRACT = 5; // number of bits to extract from the char
//	const unsigned long STOP_THRESHOLD = 1 << (LONG_BITS - CHAR_EXTRACT - 1);
//	                            // determines when the operation should stop 
//	                            //  adding characters and instead modulo
//	const unsigned char MASK = (1 << CHAR_EXTRACT) - 1;
//	                            // mask for extracting LSB
//
//	// stores the output of this operation
//	unsigned long output = 0;
//
//	for (auto itr = s.begin(); itr != s.end(); itr++) {
//		// extract the LSB from the character
//		// I get to use single & ! yay...
//		char c = *itr & MASK;
//		// push it into the output
//		output = (output << CHAR_EXTRACT) + c;
//		// if the long is about to overflow, modulo it
//		if (output > STOP_THRESHOLD) {
//			output %= n;
//		}
//	}
//
//	// the string has been traversed
//	// final modulo in case it terminated early but didn't reach threshold
//	return (unsigned int) (output % n);
//}