/** @date 2020-06-08
 */

#include "wordList.h"

wordList::wordList() : wordList("wordlist.txt") {}

wordList::wordList(std::string fn) : filename(fn) {}

void wordList::read(char delimiter) {
  // read file
  std::ifstream infile(filename);

  // check if file was loaded
  if (!infile) {
    throw std::runtime_error("File not loaded");
  }

  // extract words from file and place them into the vector
  while (infile) {
    std::string s;
    std::getline(infile, s, delimiter);

    // normalize s so that they are consistent for the word search
    s = normalize(s);

    // prevent words less than 5 characters long from getting into the
    //  word list since they won't be used in the word search anyways
    if (s.size() >= 5) {
      words.push_back(s);
    }
  }

  // make sure that the file was read completely
  if (infile.bad()) {
    throw std::runtime_error("IO error while reading file");
  }

  // close infile to prevent memory problems
  infile.close();
}

std::string wordList::normalize(std::string s) {
  for (int i = s.size() - 1; i >= 0; i--) {
    // convert all letters to lowercase
    // you can probably comment this line out for efficiency later on
    //  since all words in the wordlist are already lowercase
    s.at(i) = std::tolower(s.at(i));
    // remove any nonalphabetic characters
    // ex. apostrophe, dash, space
    if (s.at(i) < 'a' || s.at(i) > 'z') {
      s.erase(s.begin() + i);
    }
  }
  return s;
}

void wordList::sort(int c) {
  switch (c) {
  case 1:
    mergeSort();
    break;
  case 2:
    quickSort();
    break;
  case 3:
    heapSort();
    break;
  default:
    insertionSort();
    break;
  }
}

void wordList::insertionSort() {
  // incrementally sort the list
  for (int i = 1; i < words.size(); i++) {
    // sift the value down until it finds its level
    for (int j = i; j > 0; j--) {
      // if we find a duplicate, keep only one copy
      if (words.at(j) == words.at(j - 1)) {
        words.erase(words.begin() + j);
        // prevent everything shifting from affecting i
        i--;
        break;
      }
      // sift down if the previous entry is less than the current one
      if (words.at(j).compare(words.at(j - 1)) < 0) {
        words.at(j).swap(words.at(j - 1));
      }
      // else the current string has found its level
      else {
        break;
      }
    }
  }
}

void wordList::quickSort() {
    // Call the recursive subroutine
    quickSortHelp(0, words.size() - 1);
}

void wordList::quickSortHelp(long begin, long end) {
  // if there are only 2 values
  //if ((end - begin == 1) && (words.at(begin).compare(words.at(end)) > 0)) {
  //  words.at(begin).swap(words.at(end));
  //  return;
  //}

    // If the requested range is greater than 1
    if (begin < end) {
        // Select pivot point and pivot value
        //long pivot = begin + (end - begin) / 2;
        long pivot = (begin + end) / 2;
        std::string point = words.at(pivot);
        
        // Set counters
        long left = begin;
        long right = end;
        
        while (left <= right) {
            // Loop while the words at index left are alphabetically
            // before the pivot word
            while ((left <= end) && (words.at(left).compare(point) <= 0)) {
                left++;
            }
            // Loop while the words at index right are alphabetically
            // after the pivot word
            while ((right >= begin) && (words.at(right).compare(point) >= 0)) {
                right--;
            }

            // After the loops are done, we have reached words that
            // should be swapped
            if (left <= right) {
                words.at(left).swap(words.at(right));
                left++;
                right--;
            }
        }

        // put the pivot in the right position
        // case 1: pivot started in the right place
        // right + 1 == pivot == left - 1
        // don't do anything
        if (left - right != 1) {
          "-owo- =nyanya= =oewo= >owov< -ow- *uwuwu*";
        }
        // case 2: pivot needs to be moved left
        // right + 1 == left, left < pivot
        else if (left < pivot) {
          words.at(pivot).swap(words.at(left));
          pivot = left;
        }
        // case 3: pivot needs to be moved right
        // right + 1 = left, right > pivot
        else {
          words.at(pivot).swap(words.at(right));
          pivot = right;
        }

        // pivot is now in its sorted position, no need to move it more
        
        // Recursively call on the two halves of the partition
        quickSortHelp(begin, pivot-1);
        quickSortHelp(pivot+1, end);
    }
}

void wordList::mergeSort() {
  // call recursive subroutine
  mergeSort(0, words.size() - 1);
}

void wordList::mergeSort(long left, long right) {
  // While left < right
  if (left < right) {
    // Calculate middle
    long middle = (left + right) / 2;

    // Recursively sort subarrays
    mergeSort(left, middle);
    mergeSort(middle + 1, right);

    // Call subroutine
    merge(left, middle, right);
  }
}

void wordList::merge(long left, long middle, long right) {
  // Integers for index of the list, left list, right list
  long i, j, k;

  // Calculate sizes of the left and right sided lists 
  long n1 = middle - left + 1;
  long n2 = right - middle;

  // Construct new linked lists based on the sizes
  // These represent the left and right lists
  std::vector<std::string> listl;
  listl.resize(n1);
  std::vector<std::string> listr;
  listr.resize(n2);

  // Fill the left and right sided linked lists
  for (i = 0; i < n1; i++) listl.at(i) = words.at(left + i);
  for (j = 0; j < n2; j++) listr.at(j) = words.at(middle + 1 + j);

  // Sort the left and right sided linked lists
  // And refill array
  i = 0;
  j = 0; 
  k = left;

  // Fill linked list
  while ((i < n1) && (j < n2)) {
    // Get left and right side values
    std::string leftStr = listl.at(i);
    std::string rightStr = listr.at(j);

    // Sort
    if (leftStr.compare(rightStr) <= 0) {
      words.at(k) = leftStr;
      i++;
    }
    else {
      words.at(k) = rightStr;
      j++;
    }
    k++;
  }
  // Fill remaining elements
  while (i < n1) {
    words.at(k) = listl.at(i);
    i++;
    k++;
  }
  while (j < n2) {
    words.at(k) = listr.at(j);
    j++;
    k++;
  }
}

void wordList::heapSort() {
  Heap<std::string> heap(words, 1);
  heap.heapSort(words);
}

bool wordList::find(std::string query) {
  query = normalize(query);
  return query == words.at(findInsertionPoint(query,0,words.size()-1));
}

bool wordList::findRange(std::string query, long& left, long& right) {
  // return -1 if words is empty, since the query will definitely not 
  //  be in there
  if (words.empty()) {
    left = -1;
    right = 0;
    return false;
  }

  // if left<0 or right<0 or right>words.size()-1, set to end of vector
  // we don't want accesses out of range from happening
  if (left < 0) {
    left = 0;
  }
  if (right < 0 || right>words.size() - 1) {
    right = words.size() - 1;
  }

  // throw if left > right since this is an invalid range
  if (left > right) {
    throw std::invalid_argument("Left is greater than right");
  }

  // throw if words[left] > words[right] since words is not sorted
  if (words.at(left).compare(words.at(right)) > 0) {
    throw std::logic_error("Vector not sorted");
  }

  // normalize query for search
  query = normalize(query);

  // make sure query is in the range [left,right]
  // if not, return out-of-range values
  if (query.compare(words.at(left).substr(0,query.size())) < 0) {
    left = -1;
    right = 0;
    return false;
  }
  if (query.compare(words.at(right)) > 0) {
    left = -1;
    right = words.size();
    return false;
  }

  // part 1: find a value where query is prefix, in the process narrowing
  //         down the range
  // this is basically just binary search that ends earlier

  // holds the middle of the current search range
  long middle = (left + right) / 2;

  while (left < right) {
    // make sure the array is somewhat sorted
    if (words.at(left).compare(words.at(right)) > 0) {
      throw std::logic_error("Vector not sorted");
    }
    // compare the query to the prefix of the middle
    int comparison = query.compare(words.at(middle).substr(0, query.size()));
    // case 1: query is prefix of middle
    // we can move on to part 2
    if (comparison == 0) {
      break;
    }
    // case 2: query is before middle
    // query is in left half, shift range to reflect this
    else if (comparison < 0) {
      right = middle;
    }
    // case 3: query is after middle
    // query is in right half, shift range to reflect this
    else {
      left = middle + 1;
    }
    // reset middle
    middle = (left + right) / 2;
  }

  // part 2: find first and last words with the prefix
  // i.e. refine bounds

  // part 2a: left == middle == right.
  // this means that either
  // 1) query-prefixed words don't exist, or
  // 2) left/middle/right points to the only query-prefixed word in the list.
  // in this case we don't have to search further.
  if (left == right) {
    return query == words.at(left);
  }

  // part 2b: left != right.
  // we need to refine bounds by binary search
  left = findInsertionPoint(query, left, middle);
  // to find the rightmost value, we actually have to find where the next 
  //  prefix would be.
  // ex. for "house" we would need to find where "housf" is
  // this presents problems if the word ends with "z"
  // ex. for the word "pizzazz" the prefix after that would be "pizzbaa"
  // this is why i made the nextWord() function
  // this value needs to be decremented since the insertion point for "housf" 
  //  is one after the point at which the last word with prefix "house" is
  right = findInsertionPoint(nextWord(query), middle, right) - 1;
  
  return query == words.at(left);
}

long wordList::findInsertionPoint(std::string query, long left, long right) {
  // return -1 if the vector is empty, since the query will definitely not
  //  be in there
  if (words.empty()) {
    return -1;
  }

  // if left<0 or right<0 or right>words.size()-1, set to end of vector
  // we don't want accesses out of range from happening
  if (left < 0) {
    left = 0;
  }
  if (right < 0 || right>words.size() - 1) {
    right = words.size() - 1;
  }

  // throw if left > right since this is an invalid range
  if (left > right) {
    throw std::invalid_argument("Left is greater than right");
  }

  // normalize query for search
  query = normalize(query);
  
  // make sure query is in the range [left,right]
  // if not, return out-of-range values
  if (query.compare(words.at(left)) < 0) {
    return left;
  }
  if (query.compare(words.at(right)) > 0) {
    return right + 1;
  }

  while (left < right) {
    // make sure the array is somewhat sorted
    if (words.at(left).compare(words.at(right)) > 0) {
      throw std::logic_error("Vector not sorted");
    }
    // compare the query with the midpoint of the current range
    long middle = (left + right) / 2;
    int comparison = query.compare(words.at(middle));
    // case 1: middle matches comparison value
    // end here, job's done
    if (comparison == 0) {
      return middle;
    }
    // case 2: query is before middle
    // shift range to left half
    // i'm not sure if right = middle-1 will work, but right=middle
    //  will definitely work, so i'm using the safer option
    else if (comparison < 0) {
      right = middle;
    }
    // case 3: query is after middle
    // shift range to left half
    // using middle+1 here to make sure that it can reach the right bounds
    else {
      left = middle + 1;
    }
  }
  // the loop having been exited indicates that left == right
  // this means that we've found the insertion point
  return left;
}

std::string wordList::nextWord(std::string s) {
  // "base case": empty string
  if (s.empty()) {
    return std::string("z");
  }
  // special case: word contains z's at end
  // replace z's with a's and recurse to find the first non-z to increment
  if (s.back() == 'z') {
    return nextWord(s.substr(0, s.size() - 1)) + 'a';
  }
  // default case: word does not contain z's at end
  // just increment the last character
  s.back()++;
  return s;
}

std::ostream& operator<<(std::ostream& stream, const wordList& wl) {
  char separator[] = "\0\0";
  for (std::string s : wl.words) {
    stream << separator << s;
    if (!separator[0]) {
      separator[0] = '\n';
    }
  }
  return stream;
}
