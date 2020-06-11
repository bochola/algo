// IMPORTS
#include <string>   // For strings
#include <vector>   // For vectors
// Utilizing std namespace
using namespace std;

// Define header file
#ifndef HEAP_H
#define HEAP_H

/**
 * Heap is a template class that stores objects 
 * in a heap of type vector<T> and includes functions
 * to initalize, build, acess, and mutuate elements
 * for the heap. The class alos includes a heap sort function.
 */ 
template <class T>
class Heap {
    private:
        // The heap stored as a vector
        vector<T> heap;

        // Integer to store the heap structure
        // 0: None, 1: MaxHeap, 2: MinHeap
        int heapstruct;

        /**
         * The max heapify subroutine.
         * Heapifies a tree with the root at a given index.
         * 
         * @param i the given index
         * @param sz the size of the heap
         * @return void
         */
        void maxHeapify(int i, int sz) {
            // Set parent, left, and right indices
            int parent = i;
            int left = this->left(i);
            int right = this->right(i);
            
            // Change parent indices based on value comparisions
            if (left < sz && this->heap[left] > this->heap[parent]) parent = left; 
            if (right < sz && this->heap[right] > this->heap[parent]) parent = right; 
            if (parent != i) { 
                // Swap values at parent and index i
                swap(this->heap[i], this->heap[parent]); 
        
                // Recursive call to heapify
                maxHeapify(parent, sz); 
            }
        }

        /**
         * The build maximum heap subroutine.
         * Builds a max heap structure from the heap vector.
         * 
         * @param void
         * @return void
         */
        void buildMaxHeap() {
            int sz = this->heap.size();
            // Start from last non-leaf node
            int start = (sz/2 - 1);

            // Traverse from last non-leaf node and heapify each node
            for(int i = start; i >= 0; i--) this->maxHeapify(i, sz);
        }

        /**
         * The min heapify subroutine.
         * Heapifies a tree with the root at a given index.
         * 
         * @param i the given index
         * @param sz the size of the heap
         * @return void
         */
        void minHeapify(int i, int sz) {
            // Set parent, left, and right indices
            int parent = i;
            int left = this->left(i);
            int right = this->right(i);
            
            // Change parent indices based on value comparisions
            if (left < sz && this->heap[left] < this->heap[parent]) parent = left; 
            if (right < sz && this->heap[right] < this->heap[parent]) parent = right; 
            if (parent != i) { 
                // Swap values at parent and index i
                swap(this->heap[i], this->heap[parent]); 
        
                // Recursive call to heapify
                maxHeapify(parent, sz); 
            }
        }

        /**
         * The build minimum heap subroutine.
         * Builds a min heap structure from the heap vector.
         * 
         * @param void
         * @return void
         */
        void buildMinHeap() {
            int sz = this->heap.size();
            // Start from last non-leaf node
            int start = (sz/2 - 1);

            // Traverse from last non-leaf node and heapify each node
            for(int i = start; i >= 0; i--) this->minHeapify(i, sz);
        }

        /**
         * The max heapify subroutine for an inputted vector.
         * Heapifies a tree with the root at a given index.
         * 
         * @param v the input vector
         * @param i the given index
         * @param sz the size of the heap
         * @return void
         */
        void maxHeapify(vector<T>& v, int i, int sz) { 
            // Set parent, left, and right indices
            int parent = i;
            int left = this->left(i);
            int right = this->right(i);
            
            // Change parent indices based on value comparisions
            if (left < sz && v[left] > v[parent]) parent = left; 
            if (right < sz && v[right] > v[parent]) parent = right; 
            if (parent != i) { 
                // Swap values at parent and index i
                swap(v[i], v[parent]); 
        
                // Recursive call to heapify
                maxHeapify(v, parent, sz); 
            } 
        } 

        /**
         * The build maximum heap subroutine for an input vector.
         * Builds a max heap structure from the input vector.
         * 
         * @param v the input vector
         * @return void
         */
        void buildMaxHeap(vector<T>& v) {
            int sz = v.size();
            // Start from last non-leaf node
            int start = (sz/2 - 1);

            // Traverse from last non-leaf node and heapify each node
            for(int i = start; i >= 0; i--) this->maxHeapify(v,i,sz);
        }

        /**
         * The min heapify subroutine for an inputted vector.
         * Heapifies a tree with the root at a given index.
         * 
         * @param v the input vector
         * @param i the given index
         * @param sz the size of the heap
         * @return void
         */
        void minHeapify(vector<T>& v, int i, int sz) { 
            // Set parent, left, and right indices
            int parent = i;
            int left = this->left(i);
            int right = this->right(i);
            
            // Change parent indices based on value comparisions
            if (left < sz && v[left] < v[parent]) parent = left; 
            if (right < sz && v[right] < v[parent]) parent = right; 
            if (parent != i) { 
                // Swap values at parent and index i
                swap(v[i], v[parent]); 
        
                // Recursive call to heapify
                minHeapify(v, parent, sz); 
            } 
        } 

        /**
         * The build minimum heap subroutine for an input vector.
         * Builds a min heap structure from the input vector.
         * 
         * @param v the input vector
         * @return void
         */
        void buildMinHeap(vector<T>& v) {
            int sz = v.size();
            // Start from last non-leaf node
            int start = (sz/2 - 1);

            // Traverse from last non-leaf node and heapify each node
            for(int i = start; i >= 0; i--) this->minHeapify(v,i,sz);
        }

        /**
         * (Re)builds a heap based on the heap structure field.
         * 
         * If the heap structure field is 1, then a max heap is built.
         * If the heap structure field is 2, then a min heap is built.
         * 
         * @param void
         * @return void
         */ 
        void heapBuild() {
            // Based on heap struct build the heap
            if(this->heapstruct == 1) this->buildMaxHeap();
            if(this->heapstruct == 2) this->buildMinHeap();
        }

    public:
        /**
         * Default Constructor for a Heap.
         * Generates an empty heap.
         * 
         * @param void
         */ 
        Heap() {
            // Initalize empty heap (vector)
            this->heap = vector<T>();
            // Initiialize heap structure int
            this->heapstruct = 0;
        }

        /**
         * Constructor a Heap given a vector of elements.
         * Fills the heap with the vector given by a
         * specified heap structure by an integer value.
         * 1: specifies max heap.
         * 2: specifies min heap.
         * 
         * @param v the vector of elements
         * @param heapstruct
         */ 
        Heap(vector<T> v, int heapstruct) {
            // Set heap to the vector
            this->heap = v;
            // Initiialize heap structure int
            this->heapstruct = heapstruct;
            // Heapify heap
            this->heapBuild();
        }

        /**
         * Default Destructor for a Heap.
         * Destroys the heap.
         * 
         * @param void
         */ 
        ~Heap() {
            // Clear heap
            this->heap.clear();
        }

        /**
         * Converts the Heap to a string
         * Can be used to print out the Heap.
         * 
         * @param heap the Heap object
         * @return a string showing the values stored within the Heap
         */
        friend string to_string(const Heap<T> heap) {
            string out = "(";
            int sz = heap.heap.size();
            for(int i = 0; i < sz; i++) {
                if(i != 0) out = out + ", ";
                out = out + to_string(heap.heap[i]);
            }
            out = out + ")";
            return out;
        }

        /**
         * Returns the index of a parent node for a child at a specified index.
         * Returns -1 if the index is out of range.
         * 
         * @param i the specified index
         * @return the index of the parent node, -1 if the specified index is out of range
         */ 
        int parent(int i) {
            return (i-1)/2;
        }

        /**
         * Returns the index of the left child of a parent node at a specified index.
         * Returns -1 if the index is out of range.
         * 
         * @param i the specified index
         * @return the index of the left child node, -1 if the specified index is out of range
         */ 
        int left(int i) {
            return 2*i + 1;
        }

        /**
         * Returns the index of the right child of a parent node at a specified index.
         * Returns -1 if the index is out of range.
         * 
         * @param i the specified index
         * @return the index of the right child node, -1 if the specified index is out of range
         */ 
        int right(int i) {
            return 2*i + 2;
        }

        /**
         * Inserts a value into the heap and preserves the heap structure 
         * if specified before.
         * 
         * @param value the value to insert into the heap
         * @return void
         */ 
        void insert(T value) {
            // Insert element
            this->heap.pushback(value);
            // Preserve heap structure
            this->heapBuild();
        }

        /**
         * Removes a value at a specified index and preserves the heap structure
         * if specified before.
         * No elements are removed if the index is out of range.
         * 
         * @param i the index to remove a value at
         * @return void
         */ 
        void remove(int i) {
            // Get heap size
            int sz = this->heap.size();

            // If the index is in range remove the element from the heap
            if(i < sz && i >= 0) this->heap.erase(this->heap.begin() + i);

            // Preserve heap structure
            this->heapBuild();
        }

        /**
         * Acesses an element at a specified index in the heap.
         * 
         * @param i the specified index
         * @return the element at the specified index
         * @throw out_of_range exception if the index is out of range
         */ 
        T getItem(int i) {
            int sz = this->heap.size();
            if(i < sz && i >= 0) return this->heap[i];
            else throw out_of_range("Index: " + to_string(i) + " is out of range, range is: [0, " + to_string(sz) + "]");
        }

        /**
         * Mutates an element at a specified index in the heap.
         * Does not mutuate any elements if the speciifed index is out of range.
         * The function does preserve any previously specified heap structures.
         * 
         * @param i the specified index
         * @param value the mutating value
         */ 
        void setItem(int i, T value) {
            // Get heap size
            int sz = this->heap.size();

            // If index is in range then update the value
            if(i < sz && i >= 0) this->heap[i] = value;
        }

        /**
         * Function creates a max heap structure.
         * 
         * @param void
         * @return void
         */ 
        void initializeMaxHeap() {
            // Set heap structure int
            this->heapstruct = 1;

            // Build max heap
            this->buildMaxHeap();
        }

        /**
         * Function creates a min heap structure.
         * 
         * @param void
         * @return void
         */ 
        void initializeMinHeap() {
            // Set heap structure int
            this->heapstruct = 2;

            // Build min heap
            this->buildMinHeap();
        }

        /**
         * Sorts a vector using heap sort.
         * 
         * @param v the vector to sort
         * @return void
         */ 
        void heapSort(vector<T>& v) { 
            // Get last index
            int last = v.size() - 1;

            // Build max heap
            this->buildMaxHeap(v);
        
            // One by one extract an element from heap 
            for (int i = last; i > 0; i--) 
            { 
                // Move current root to end 
                swap(v[0], v[i]); 
        
                // call max heapify on the reduced heap 
                maxHeapify(v, 0, i); 
            } 
        } 

        /**
         * Acessor for the vector storing the heap.
         * 
         * @param void
         * @return the vector storing the heap
         */ 
        vector<T> getHeap() {
            return this->heap;
        }
};

#endif