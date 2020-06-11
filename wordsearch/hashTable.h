#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <fstream>
#include <string>
#include <vector>

#include "wordList.h"

/** Special modulo operator to facilitate hashing of strings.
 * The string gets interpreted as a 5*n bit unsigned binary number,
 *  where n is the length of the string.
 * Each character is cut to the 5 least significant bits and the string's
 *  character-bits are concatenated, first character becoming the most
 *  significant bits of the resulting bitstring.
 * @param s The string to be modulo-ed
 * @param l The modul-ator
 * @return The result of the pseudo-modulo operation, as described above
 */
unsigned int operator%(std::string s, unsigned int n);

/** Implements a hash table using modulo-based hashing.
 */

template <class T> class hashTable {
private:
  /** Stores the hash table.
   * Resolves hash collisions by chaining into the nested vector.
   */
  std::vector<std::vector<T> > table;
  
  /** Stores the length of the longest value in the hash table.
   */
  int largest;

public:
  /* * * CONSTRUCTORS * * */

  /** Creates am empty hash table of size 53017
   */
  hashTable();

  /** Creates an empty hash table.
   * Default size is 53017 (approx. 2^15 * phi)
   */
  hashTable(unsigned int size);

  /* * * ACCESSORS * * */

  /** Searches for t in the hash table.
   * @param t Item to be searched for
   * @return true If the item was found in the hash table,
   *         false otherwise
   */
  bool inList(T t);

  /** Returns the size of the largest value in this hash table.
   * @return The size of the largest value in this hash table.
   */
  int getLargest();

  /* * * MUTATORS * * */

  /** Inserts t into the hash table.
   * @param t Item to be inserted into the hash table.
   */
  void addItem(T t);

  /** Inserts all values of the vector into the hash table.
   * @param vec Vector to be batch-inserted into the hash table.
   */
  void addVector(std::vector<T> vec);

  /** Deletes all instances of t from the hash table.
   * @param t Item to be removed from hash table
   * @return Number of copies removed, zero (0) if none removed
   */
  int removeItem(T t);

  /** Reads the source file and loads them into the hash table.
   * Assumes that the wordlist file contains only lowercase Latin letters and
   *  that words are consistently delimited by whitespace (space or newline)
   * Also assumes that operator>> is defined for T.
   * @param filename The path of the file.
   * @throw runtime_error If the file was not able to be read.
   */
  void read(std::string filename);

  /* * * UTILITY * * */

  /** Computes the hash value of the input.
   * Assumes T has a modulo operator that can take integral data types
   *  (char, short, int, long) in the second position.
   * For this implementation, will hash into the range [0,53017).
   * @param t The value to be hashed
   * @return The hashed value of t
   */
  unsigned int hash(T t);
};

inline unsigned int operator%(std::string s, unsigned int n) {
  // This algorithm is based on the modular arithmetic identities
  // (a*b)(mod n) = ((a mod n) * b)(mod n) and
  // (a+b)(mod n) = ((a mod n) + (b mod n))(mod n)
  // This allows this to process up to 3 characters at a time using longs.
  // Grouping the characters into blocks reduces the number of modulos 
  //  required, marginally increasing performance since modulos are probably 
  //  the most expensive part of this algorithm.
  // Unfortunately, this means this operation is not constant-time, but linear 
  //  to the length of the string. Smaller values of n will also run faster
  //  since the "modulo crunch" is more significant for smaller bases, allowing 
  //  more characters to fill up in between modulos.
  // I used the 5 least significant bits because those encode the values of 
  //  Latin letters in ASCII/Basic Latin. The 3 MSB are always 010 for
  //  uppercase and 011 for lowercase, but since for this project we don't care
  //  about case (and everything is in lowercase anyways), keeping the 3 MSB 
  //  is essentially boilerplate that will make the hashing algorithm less like 
  //  simple uniform hashing.
  // I used the 5 LSB instead of base-26 in case we decided that special 
  //  characters (ex. apostrophes, dashes, spaces) were important for the 
  //  project. These values could be mapped to the empty spaces 0 or 26-31.
  //  Also, truncating to the 5 LSB is easier to implement and probably faster 
  //  than trying to trim it tight to base-26.

  // parameters of the modulo operation
  const int LONG_BITS = 32;   // number of bits in a long
  const int CHAR_EXTRACT = 5; // number of bits to extract from the char
  const unsigned long STOP_THRESHOLD = 1 << (LONG_BITS - CHAR_EXTRACT - 1);
  // determines when the operation should stop 
  //  adding characters and instead modulo
  const unsigned char MASK = (1 << CHAR_EXTRACT) - 1;
  // mask for extracting LSB

// stores the output of this operation
  unsigned long output = 0;

  for (auto itr = s.begin(); itr != s.end(); itr++) {
    // extract the LSB from the character
    // I get to use single & ! yay...
    char c = *itr & MASK;
    // push it into the output
    output = (output << CHAR_EXTRACT) + c;
    // if the long is about to overflow, modulo it
    if (output > STOP_THRESHOLD) {
      output %= n;
    }
  }

  // the string has been traversed
  // final modulo in case it terminated early but didn't reach threshold
  return (unsigned int)(output % n);
}

template<class T> inline hashTable<T>::hashTable() : hashTable(53017) {}

template<class T> inline hashTable<T>::hashTable(unsigned int size)
  : table(size), largest(0) {}

template<class T> inline bool hashTable<T>::inList(T t) {
  // traverse the slot and try to find the query
  for (auto i : table.at(hash(t))) {
    if (t == i) {
      return true;
    }
  }
  return false;
}

template<class T> inline int hashTable<T>::getLargest() {
  return largest;
}

template<class T> inline void hashTable<T>::addItem(T t) {
  table.at(hash(t)).push_back(t);
  if (t.size() > largest) {
    largest = t.size();
  }
}

template<class T> inline void hashTable<T>::addVector(std::vector<T> vec) {
  for (T t : vec) {
    addItem(t);
  }
}

template<class T> inline int hashTable<T>::removeItem(T t) {
  // stores the number of times t was removed
  int output = 0;
  // alias to slot to make the rest easier
  std::vector<T>& slot = table.at(hash(t));
  // remove element, starting from back to prevent increment shenanigans
  for (int i = slot.size() - 1; i >= 0; i--) {
    if (slot.at(i) == t) {
      slot.erase(slot.begin() + i);
      output++;
    }
  }
  return output;
}

template<class T> inline void hashTable<T>::read(std::string filename) {
  // read file
  std::ifstream infile(filename);

  // check if file was loaded
  if (!infile) {
    throw std::runtime_error("File not loaded");
  }

  // extract words from file and place them into the vector
  while (infile) {
    T s;
    infile >> s;

    // normalize s so that they are consistent for the word search
    s = wordList::normalize(s);

    // prevent words less than 5 characters long from getting into the
    //  word list since they won't be used in the word search anyways
    // comment this out if this is ever used for not-strings.
    if (s.size() >= 5) {
      addItem(s);
    }
  }

  // make sure that the file was read completely
  if (infile.bad()) {
    throw std::runtime_error("IO error while reading file");
  }

  // close infile to prevent memory problems
  infile.close();
}

template<class T> inline unsigned int hashTable<T>::hash(T t) {
  return t % table.size();
}

#endif