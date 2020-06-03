// IMPORTS
// Utilizing std namespace
using namespace std;
#include <string>   // For strings
#include <vector>   // For vectors

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

        // The heap size 
        // NOTE: May not need this
        int heap_sz;

        /**
         * The max heapify subroutine.
         * Heapifies a tree with the root at a given index.
         * 
         * @param i the given index
         * @return void
         */
        void maxHeapify(int i);

        /**
         * The build maximum heap subroutine.
         * Builds a max heap structure from the heap vector.
         * 
         * @param void
         * @return void
         */
        void buildMaxHeap();

        /**
         * The min heapify subroutine.
         * Heapifies a tree with the root at a given index.
         * 
         * @param i the given index
         * @return void
         */
        void minHeapify(int i);

        /**
         * The build minimum heap subroutine.
         * Builds a min heap structure from the heap vector.
         * 
         * @param void
         * @return void
         */
        void buildMinHeap();

    public:
        /**
         * Default Constricted for a Heap.
         * Generates an empty heap.
         * 
         * @param void
         */ 
        Heap();

        /**
         * Default Destructor for a Heap.
         * Destroys the heap.
         * 
         * @param void
         */ 
        ~Heap();

        /**
         * Converts the Heap to a string
         * Can be used to print out the Heap.
         * 
         * @param heap the Heap object
         * @return a string showing the values stored within the Heap
         */
        // NOTE: Function may not be needed
        friend string to_string(const Heap<T> heap);

        /**
         * Returns the index of a parent node for a child at a specified index.
         * Returns -1 if the index is out of range.
         * 
         * @param i the specified index
         * @return the index of the parent node, -1 if the specified index is out of range
         */ 
        int parent(int i);

        /**
         * Returns the index of the left child of a parent node at a specified index.
         * Returns -1 if the index is out of range.
         * 
         * @param i the specified index
         * @return the index of the left child node, -1 if the specified index is out of range
         */ 
        int left(int i);

        /**
         * Returns the index of the right child of a parent node at a specified index.
         * Returns -1 if the index is out of range.
         * 
         * @param i the specified index
         * @return the index of the right child node, -1 if the specified index is out of range
         */ 
        int right(int i);

        /**
         * Acesses an element at a specified index in the heap.
         * 
         * @param i the specified index
         * @return the element at the specified index
         * @throw out_of_range exception if the index is out of range
         */ 
        T getItem(int i);

        /**
         * Mutates an element at a specified index in the heap.
         * Does not mutuate any elements if the speciifed index is out of range.
         * 
         * @param i the specified index
         * @param value the mutating value
         */ 
        void setItem(int i, T value);

        /**
         * Function creates a max heap structure.
         * 
         * @param void
         * @return void
         */ 
        void initializeMaxHeap();

        /**
         * Function creates a min heap structure.
         * 
         * @param void
         * @return void
         */ 
        void initializeMinHeap();

        /**
         * Sorts a vector using heap sort.
         * 
         * @param v the vector to sort
         * @return void
         */ 
        void heapSort(vector<T> v);
};

#endif