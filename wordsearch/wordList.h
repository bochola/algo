#ifndef WORDLIST_H
#define WORDLIST_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "heap.h"

/** Stores a dictionary of words/strings and related utilities.
 */

class wordList {
private:
  /** Stores the dictionary of words from the file.
   */
  std::vector<std::string> words;

  /** Stores the name of the file that the word list is imported from.
   */
  std::string filename;

public:
  /* * * CONSTRUCTORS * * */

  /** A default constructor that assumes the wordlist file is named wordlist.txt.
   */
  wordList();

  /** Constructor.
   * Takes in the filename of the source word list as argument.
   * @param fn The name of the word list source file
   */
  wordList(std::string fn);

  /* * * INITIALIZATION * * */

  /** Reads the source file and loads them into the words vector.
   * Assumes that the wordlist file contains only lowercase Latin letters.
   * Does not sort the words vector.
   * @param delimiter The character that acts as the delimiter. Default newline.
   * @throw runtime_error If the file was not able to be read.
   */
  void read(char delimiter = '\n');

  /* * * NORMALIZATION * * */

  /** Normalizes a string to contain only lowercase Latin letters.
   * Removes any nonalphabetic characters and makes uppercase letters lowercase.
   * Parameter is in/out; the function modifies the parameter.
   * @param s String to be normalized
   */
  static std::string normalize(std::string s);

  /* * * PRINTING * * */

  /** Overloaded stream insertion operator.
   * Prints each word separated by newlines.
   * @param &stream The ostream to be inserted into.
   * @param &wl The wordlist to be inserted into the stream.
   * @return stream So insertions can be chained
   */
  friend std::ostream& operator<<(std::ostream& stream, const wordList& wl);

  /* * * SORTING * * */

  /** Generic function to package all the other sorting functions.
   * The function body should only contain a call to a specific sorting algorithm.
   * Codes:
   * 0 = insertion sort
   * 1 = merge sort
   * 2 = quicksort
   * 3 = heap sort
   * @param A code representing the type of sort requested, as described above
   */
  void sort(int c = 0);

  /** Sorts the words vector using insertion sort.
   * Also removes duplicates from the vector.
   */
  void insertionSort();

  /** Sorts the words vector using merge sort.
   */
  void mergeSort();

  /** Sorts the words vector using quicksort.
   */
  void quickSort();

private:
  /** A utility function to facilitate the recursive calls of merge sort.
   * Only sorts a part of the words array in [left, right] (both inclusive).
   * ex. If mergeSort(1,3) was called on the vector [0,1,2,3,4,5] then it
   *      would sort the subarray [1,2,3]
   * Assumes that left < right. Won't do anything if left >= right, but also 
   *  won't throw an exception.
   * @param left The lowest index in the subarray
   * @param right The highest index in the subarray
   */
   void mergeSort(long left, long right);

   /** Merges two sorted subarrays.
    * Assumes the subarrays are already sorted.
    * @param left The first index of the left subarray
    * @param middle The last index of the left subarray or the index before
    *               the first element of the right subarray
    * @param right The last index of the right subarray
   */
  void merge(long left, long middle, long right);

  /** The helper function for quicksort to make it recursive
   * @param begin is the index of the vector to start at
   * @param end   is the index of the vector to end at
   */
  void quickSortHelp(long begin, long end);

  public:
    /** Sorts the words vector using heapsort.
     */
    void heapSort();

    /* * * SEARCHING * * */

public:
  /** Searches for a word in the words vector using binary search.
   * Assumes that the vector is already sorted.
   * Does not necessarily check if the vector is sorted, but will throw an
   *  exception if it detects a state that would indicate that the words
   *  vector is not sorted.
   * @param query The word to be searched for
   * @return true If query is in the words vector,
   *         false otherwise
   * @throw logic_error If the algorithm detects that the vector is unsorted
   */
  bool find(std::string query);

  /** Searches for a range of words that start with the query.
   * ex. query "house" will return the start and end indices of the range
   *      containing [HOUSE, HOUSEhold, HOUSEplant] &c. but not the words
   *      "reHOUSE", "tHOUSand", "HOUSing" (emphasis added, actual ranges will
   *      be all lowercase)
   * Indices returned via in/out parameters are the first (left) and last
   *  (right) words in the range.
   * ex. query "ours" in the vector [hour,our,ours,ourself,us,we] will
   *      return true, out-parameters left=2 and right=3.
   * In addition, the function itself will return true if the string itself is
   *  in the vector. If the return is true, then the query will be at
   *  words[left].  In this way it can be used as binary search with extra
   *  functionality.
   * ex. query "ours" in the vector [hour,our,ours,ourself,us,we] will return
   *      true, while query "ou" will return false.
   * If no values with the query as prefix are found in the specified range,
   *  left will be set to -1, and right will be set to the index where the
   *  query should be inserted to keep the vector sorted.
   * ex. query "hours" in the vector [hour,our,ours,ourself,us,we] will return
   *      false, out-parameters left=-1 and right=1.
   *  This can do wonky things when the range specified is does not contain the
   *  prefix.
   * ex. findRange("me",4,5) on the vector [hour,our,ours,ourself,us,we] will
   *      return false, out-parameters left=-1, right=4.
   * Assumption: Vector is sorted.
   *  This function will not explicitly check if the whole vector is sorted,
   *  but it will throw if it detects a state which would suggest the  words
   *  vector is not sorted.
   * Assumption for correct operation: The range of values for which the query
   *  is a prefix is included in the in-parameter range [left,right] in the
   *  words vector.
   * @param query The prefix to find the range of.
   * @param left An in/out parameter.
   *             IN:  The first index of the range to search in.
   *                  If left is passed as a negative number, this function will
   *                  assume left=0.
   *             OUT: The first index of the range that contains the query as a
   *                  prefix. If the query is in the range [left,right],
   *                  then left will be the index of query in the words vector.
   *                  If no words in the input range contain the query as a
   *                  prefix, left=-1.
   * @param right An in/out parameter.
   *              IN:  The last index of the range to search in, inclusive.
   *                   If right is passed as a negative number, this function
   *                   will assume right=words.size()-1.
   *              OUT: The last index of the range that contains the query as
   *                   an a prefix.
   *                   If no words in the input range contain the query as a
   *                   prefix, then right is the index at which the prefix
   *                   should be inserted to keep the words vector sorted.
   *                   If only one word in the input range contains the query
   *                   as a prefix, then left=right.
   * @return true If query is in the words vector range [left,right],
   *         false otherwise
   * @throw logic_error If the algorithm detects that the vector is unsorted
   * @throw invalid_argument If left > right
   */
  bool findRange(std::string query, long& left, long& right);

private:
  /** Returns the index where the query should be inserted to keep words sorted.
   * This is basically the same as binary search, except it doesn't actually
   *  say if the query is in the vector words, just where it should be. If
   *  query actually exists in the vector, this will return its index.
   * Used as a utility function for find() and findRange() to prevent code
   *  duplication.
   * If left or right are negative or out of bounds, this function will
   *  automatically reset them to the lower/upper bounds of the vector.
   * @param query The query to find the (hypothetical) insertion point of.
   * @param left The left (lower) bound of the range to be searched.
   * @param right The right (upper) bound of the range to be searched.
   * @return The index to insert query into to keep words sorted.
   * @throw logic_error If the algorithm detects that the vector is unsorted
   * @throw invalid_argument If left > right
   */
  long findInsertionPoint(std::string query, long left, long right);

  /** Returns the next "word" of the same length.
   * ex. "house" -> "housf"
   * ex. "pizzazz" -> "pizzbaa"
   * This completely breaks down if the word is all z's or empty
   * Current behavior is just to add one more z if it's all z's.
   * ex. "z" -> "zz"
   * ex. "" -> "z"
   * Assumes s is already normalized.
   * @param s Original word
   * @return The next "word" of the same length
   */
  std::string nextWord(std::string s);
};

// See lines 56-62 for documentation.
std::ostream& operator<<(std::ostream& stream, const wordList& wl);

#endif
