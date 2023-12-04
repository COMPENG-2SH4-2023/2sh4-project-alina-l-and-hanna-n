#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

// Define the maximum capacity of the array
#define ARRAY_MAX_CAP 256

#include "objPos.h"

// Declaration of the objPosArrayList class
class objPosArrayList
{
    private:
        objPos* aList; // Pointer to an array of objPos objects
        int sizeList; // Current number of elements in the list
        int sizeArray; // The total capacity of the array

    public:
        // Constructor and Destructor
        objPosArrayList(); // Default constructor
        ~objPosArrayList(); // Destructor

        // Public member functions
        int getSize(); // Method to get the current size of the list
        void insertHead(objPos thisPos); // Method to insert an element at the head
        void insertTail(objPos thisPos); // Method to insert an element at the tail
        void removeHead(); // Method to remove the head element
        void removeTail(); // Method to remove the tail element

        // Methods to get elements from the list
        void getHeadElement(objPos &returnPos); // Method to get the head element
        void getTailElement(objPos &returnPos); // Method to get the tail element
        void getElement(objPos &returnPos, int index); // Method to get an element by index
};

#endif
