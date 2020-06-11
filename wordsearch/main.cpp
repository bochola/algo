#ifndef MAIN_CPP
#define MAIN_CPP

#include <chrono>
#include <iostream>
#include <string>

#include "grid.h"
#include "hashTable.h"
#include "wordList.h"

/** Finds all matches in the grid and prints them to the console.
 * Runs in O(n^2 * w * log k) time, where 
 *  n = side length of grid, 
 *  w = longest word in the dictionary
 *  k = size of dictionary
 * Since, as puzzles grow larger, n and k tend to grow much faster than w, 
 *  the performance approaches O(n^2 * log k) time.
 * @param wl A word list representing the dictionary
 * @param g The grid to search on
 * @return The number of matches found
 */
inline long findMatches(wordList wl, Grid g) {
  long countMatches = 0;

  // for each starting point, in each direction, check for matches
  // first loop loop: row
  for (int i = 0; i < g.getRowSize(); i++) {
    // second loop: column
    for (int j = 0; j < g.getRowSize(); j++) {
      // third loop: direction
      for (int d = 0; d <= 7; d++) {
        // get the full trace from this starting point in this direction
        std::string fullTrace = g.trace(i, j, (Direction) d, g.getRowSize());
        // set up bounds for searching in the dictionary
        long left = 0;
        long right = -1; // will be set to the length of the dictionary
        // fourth loop: trace/word length
        // if left is negative, that means that no more words in the trace
        //  are in the dictionary, so we can stop early
        // this means, assuming we are using a dictionary of a 
        //  nonpolysynthetic language (ex. English, Romance langauges) 
        //  and not something agglutinative/polysynthetic like Inuit or 
        //  Ithkuil where you  can string together arbitrarily long words, 
        //  this will ultimately run a finite amount of times.
        // For English, if we remove technical (i.e. systematically-generated 
        //  scientific words, like the 180,000-ish letter long name for titin) 
        //  and contrived words (like lopadote...pterygon (182 letters) from 
        //  Aristophanes) from consideration, this leaves 
        //  "antidisestablishmentarianism" (28 letters) as the longest word in 
        //  English. As such, for larger grids, this innermost loop is 
        //  effectively capped at around 30 letters. 
        // sorry had a ling minor moment there
        for (int l = 5; l <= g.getRowSize() && left >= 0; l++) {
          // left and right are in/out parameters of findRange, so they
          //  are automatically updated
          if (wl.findRange(fullTrace.substr(0, l), left, right)) {
            // if you're in here, we've found a word! congrats!
            std::cout << "Found " << fullTrace.substr(0, l) << " at position "
              << i << "," << j << " in direction " << d << "\n";
            countMatches++;
          }
        }
      }
    }
  }
  return countMatches;
}

/** Finds all matches in the grid and prints them to the console using hash tables.
 * Runs in O(n^3) * O(h(l) + a) time, where
 *  n is the side length of the grid,
 *  l is the longest word in the dictionary, 
 *  a is the loading factor of the hash table, and
 *  h(l) is the time to hash a word of length l
 * Since our hash function is technically linear to l, this 
 *  means that this algorithm grows at O((l+a)*n^3), which is ok considering 
 *  that l and a are typically bounded.
 * @param ht A hash table representing the dictionary
 * @param g The grid to search on
 * @return The number of matches found
 */
inline long findMatches(hashTable<std::string> ht, Grid g) {
  long countMatches = 0;

  // for each starting point, in each direction, check for matches
  // first loop loop: row
  for (int i = 0; i < g.getRowSize(); i++) {
    // second loop: column
    for (int j = 0; j < g.getRowSize(); j++) {
      // third loop: direction
      for (int d = 0; d <= 7; d++) {
        // fourth loop: trace/word length
        for (int l = 5; l <= g.getRowSize() && l <= ht.getLargest(); l++) {
          // stores word at i,j in direction d of length l
          std::string currentTrace = g.trace(i, j, (Direction) d, l);
          if (ht.inList(currentTrace)) {
            // if you're in here, we've found a word! congrats!
            std::cout << "Found " << currentTrace << " at position "
              << i << "," << j << " in direction " << d << "\n";
            countMatches++;
          }
        }
      }
    }
  }
  return countMatches;
}

/** Searches for all the matches in the grid, logging time to process and search.
 * Logs time to sort/prepare the list and find all matches.
 * Parameter decides the method used to sort/search, as follows:
 *  0: insertion sort
 *  1: merge sort
 *  2: quicksort
 *  3: heap sort
 *  4: hash table
 * @param c Code to determine which method to use, as described above
 */
inline void search(int c) {
  
  wordList wl;
  hashTable<std::string> ht;
  Grid g;
  std::chrono::duration<double> totalTime = std::chrono::duration<double>::zero();

  // part 1: importing word list
  while (true) {
    std::cout << "Type in the file name of the word list file: ";
    std::string filename;
    std::cin >> filename;
    wl = wordList(filename);
    try {
      auto readStart = std::chrono::system_clock::now();
      if (c == 4) {
        ht.read(filename);
      }
      else {
        wl.read();
      }
      auto readEnd = std::chrono::system_clock::now();
      std::chrono::duration<double> readTime = readEnd - readStart;
      std::cout << "Reading wordlist file took " << readTime.count() << " seconds.\n";
      totalTime += readTime;
      break;
    }
    catch (const std::invalid_argument & ex) {
      std::cout << "Import was unsuccessful, probably because the file name was incorrect. Please try again.\n";
    }
    catch (const std::runtime_error & ex) {
      std::cout << "Import was unsuccessful, probably because the file name was incorrect. Please try again.\n";
    }
    catch (...) {
      std::cout << "Import was unsuccessful, probably because the file name was incorrect. Please try again.\n";
    }
  }

  // part 2: importing grid
  while (true) {
    std::cout << "Type in the file name of the grid file: ";
    std::string filename;
    std::cin >> filename;
    try {
      auto readStart = std::chrono::system_clock::now();
      g.open(filename);
      g.store();
      g.close();
      auto readEnd = std::chrono::system_clock::now();
      std::chrono::duration<double> readTime = readEnd - readStart;
      std::cout << "Reading grid file took " << readTime.count() << " seconds.\n";
      totalTime += readTime;
      break;
    }
    catch (const std::invalid_argument & ex) {
      std::cout << "Import was unsuccessful, probably because the file name was incorrect. Please try again.\n";
    }
    catch (const std::runtime_error & ex) {
      std::cout << "Import was unsuccessful, probably because the file name was incorrect. Please try again.\n";
    }
    catch (...) {
      std::cout << "Import was unsuccessful, probably because the file name was incorrect. Please try again.\n";
    }
  }

  // part 3: sort
  auto sortStart = std::chrono::system_clock::now();

  wl.sort(c);

  auto sortEnd = std::chrono::system_clock::now();
  std::chrono::duration<double> sortTime = sortEnd - sortStart;
  std::cout << "Sorting wordlist took " << sortTime.count() << " seconds.\n";
  totalTime += sortTime;

  // part 4: do the word search
  auto findStart = std::chrono::system_clock::now();
  // stores the number of words found
  long wordCount = -1;
  if (c == 4) {
    wordCount = findMatches(ht, g);
  }
  else {
    wordCount = findMatches(wl, g);
  }
  auto findEnd = std::chrono::system_clock::now();
  std::chrono::duration<double> findTime = findEnd - findStart;
  std::cout << "Found " << wordCount << " words in grid in " << findTime.count() << " seconds.\n";
  totalTime += findTime;

  std::cout << "Total duration: " << totalTime.count() << " seconds.\n";
}

/** Function to automatically import, sort, and search.
 * Outputs to a CSV file with headers:
 *  timestamp: The time this test started, in milliseconds since UNIX epoch
 *  wordlist: The filename of the word list
 *  grid: The filename of the grid
 *  algorithm: The algorithm used (sorting/hash table)
 *  wordlistreadtime: The time taken to load the word list in seconds
 *  gridreadtime: The time taken to load the grid in seconds
 *  sorttime: The time taken to sort the grid in seconds
 *            Will be ~0 for hash tables
 *  searchtime: The time taken to search the whole grid in seconds
 *  nummatches: The number of matches found in the grid
 * @param outfile The filename of the output log
 * @param wlfile The filename of the word list
 * @param gfile The filename of the grid
 * @param c The code that determines the sorting algorithm/hash table
 */
inline void search(std::ofstream& outfile, std::string wlfile, std::string gfile, int c) {
  wordList wl(wlfile);
  hashTable<std::string> ht;
  Grid g(gfile);

  outfile << '\n';
  // store timestamp
  outfile << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  outfile << ',';

  // store test parameters
  outfile << wlfile;
  outfile << ',';
  outfile << gfile;
  outfile << ',';
  switch (c) {
  case 0:
    outfile << "insertionsort";
    break;
  case 1:
    outfile << "mergesort";
    break;
  case 2:
    outfile << "quicksort";
    break;
  case 3:
    outfile << "heapsort";
    break;
  case 4:
    outfile << "hashtable";
    break;
  }
  outfile << ',';

  // import word list
  auto wlReadBegin = std::chrono::system_clock::now();
  if (c == 4) {
    ht.read(wlfile);
  }
  else {
    wl.read();
  }
  auto wlReadEnd = std::chrono::system_clock::now();
  std::chrono::duration<double> wlReadTime = wlReadEnd - wlReadBegin;
  outfile << wlReadTime.count();
  outfile << ',';

  // import grid
  auto gReadBegin = std::chrono::system_clock::now();
  g.open(gfile);
  g.store();
  g.close();
  auto gReadEnd = std::chrono::system_clock::now();
  std::chrono::duration<double> gReadTime = gReadEnd - gReadBegin;
  outfile << gReadTime.count();
  outfile << ',';

  // sort file
  if (c == 4) {}
  else {
    auto sortBegin = std::chrono::system_clock::now();
    wl.sort(c);
    auto sortEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> sortTime = sortEnd - sortBegin;
    outfile << sortTime.count();
  }
  outfile << ',';

  // search wordlist
  long numMatches;
  auto searchBegin = std::chrono::system_clock::now();
  if (c == 4) {
    numMatches = findMatches(ht, g);
  }
  else {
    numMatches = findMatches(wl, g);
  }
  auto searchEnd = std::chrono::system_clock::now();
  std::chrono::duration<double> searchTime = searchEnd - searchBegin;
  outfile << searchTime.count();
  outfile << ',';

  // return number of matches
  outfile << numMatches;
}

/** Runs through every combination, storing them in log.csv
 */
int main() {
  std::cout << "Start.\n";

  std::ofstream outfile("log.csv");
  outfile.clear();
  outfile << "timestamp,wordlist,grid,algorithm,wordlistreadtime,gridreadtime,sorttime,searchtime,nummatches";

  std::vector<std::string> wordlists = {
    "puzzle10-words.txt",
    "wordlist.txt",
    "wordlist2.txt"
  };

  std::vector<std::string> grids = {
    "puzzle10.txt",
    "input15.txt",
    "input30.txt",
    "input50.txt",
    "input250.txt"
  };

  for (std::string wl : wordlists) {
    for (std::string g : grids) {
      for (int c = 0; c <= 4; c++) {
        search(outfile, wl, g, c);
      }
    }
  }

  outfile.close();
}

#endif