#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

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
unsigned long operator%(std::string s, long l);

template <class T>

/** Implements a hash table.
 */

class hashTable<T> {
private:
  /** Stores the hash table.
   * Resolves hash collisions by chaining into the nested vector.
   */
  std::vector<std::vector<T> > table;
  
public:
  /* * * CONSTRUCTORS * * */
  
  /** Creates an empty hash table.
   */
  hashTable();
  
  /* * * ACCESSORS * * */
  
  /** Searches for t in the hash table.
   * @param t Item to be searched for
   * @return true If the item was found in the hash table,
   *         false otherwise
   */
  bool inList(T t);
  
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

#endif