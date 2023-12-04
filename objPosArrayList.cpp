#include "objPosArrayList.h"

// Constructor
objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // Allocate an array for 200 elements
    sizeList = 0; // Initially, no valid elements in the list
    sizeArray = ARRAY_MAX_CAP; // Set the array capacity to maximum
}

// Destructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList; // Free the allocated array
    // Note: It's crucial to use delete[] for arrays to properly deallocate memory
}

// Method to get the size of the list
int objPosArrayList::getSize()
{
    return sizeList;
}

// Method to insert an element at the head of the list
void objPosArrayList::insertHead(objPos thisPos)
{
    // Check if the list is at full capacity
    if(sizeList != ARRAY_MAX_CAP)
    {
        // Shift all elements towards the tail to make space at the head
        for(int i = sizeList; i > 0; i--)
        {
            aList[i].setObjPos(aList[i-1]);
        }
        aList[0].setObjPos(thisPos);
        sizeList++;
    }
}

// Method to insert an element at the tail of the list
void objPosArrayList::insertTail(objPos thisPos)
{
    // Check if the list is at full capacity
    if(sizeList != ARRAY_MAX_CAP)
    {
        aList[sizeList].setObjPos(thisPos); // No need to shift elements
        sizeList++;
    }
}

// Method to remove the head element of the list
void objPosArrayList::removeHead()
{
    if(sizeList != 0)
    {
        // Shift all elements towards the head
        for(int i = 0; i < sizeList; i++)
        {
            aList[i].setObjPos(aList[i+1]);
        }
        sizeList--;        
    }
}

// Method to remove the tail element of the list
void objPosArrayList::removeTail()
{   
    if(sizeList != 0)
    {
        sizeList--; // Simply decrement the size, no need to shift elements
    }
}

// Method to get the head element of the list
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

// Method to get the tail element of the list
void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

// Method to get an element at a specified index
void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}
