// list.h
// unsorted- static array implementation (with iterator)

#ifndef _LISTH_PROG3
#define _LISTH_PROG3

#include <iostream>
using namespace std;

#include "item.h" 
// Item header file must be provided by the client of this class.
// Item header file must contain the following definitions:
//   MAX_LENGTH:the maximum number of items on the list
//   ItemType:	the definition of the objects on the list

class List
{
public:

    List();
    // Default constructor
	 
    void MakeEmpty();
    // Function:  Initializes list to empty state.
    // Post: List is empty.

    bool IsFull() const;
    // Function:  Determines whether list is full.
    // Pre:  List has been initialized.
    // Post: Function value = (list is full)

    bool IsEmpty() const;
    // Function:  Determines whether list is empty.
    // Pre:  List has been initialized.
    // Post: Function value = (list is empty)

    int Length() const;
    // Function: Determines the number of elements in list.
    // Pre:  List has been initialized.
    // Post: Function value = number of elements in list

    bool Retrieve(ItemType& item) const;
    // Function: Retrieves list item whose key matches item's key (if 
    //           present).
    // Pre:  List has been initialized.
    //       Key member of item is initialized.
    // Post: If there is a list item someItem whose key matches 
    //       item's key, then
    //				return val = true and item is a copy of
    //       someItem; 
    //			otherwise return val= false and item is unchanged. 
    //       List is unchanged.

    bool Insert(ItemType item);
    // Function: Adds element to list.
    // Pre:  List has been initialized.
    //       List is not full. 
    // Post: item is in list.
 
    bool Delete(ItemType item);
    // Function: Deletes the list item whose key matches item's key.
    // Pre:  List has been initialized.
    //       Key member of item is initialized.
    // Post: That item is no longer in list.
 
    bool IsPresent(ItemType item) const;
    // Function: Checks if item is in the list based on the key
    // Pre:  List has been initialized.
    //       Key member of item is initialized.
    // Post: If there is a list item someItem whose key matches 
    //       item's key, then
    //				return val = true
    //			otherwise return val= false
	 
    void SelSort();
    // Function: Sorts the list in ascending order
    // Pre:  List has been initialized
    // Post: List is sorted in ascending order based on key field(s).
	 
    void Reset();
    // Function: Initializes current position for
    //           an iteration through the list.
    // Post: Current position is prior to list.

    void GetNextItem(ItemType& item);
    // Function: Gets the next element in list.
    // Pre:  Current position is defined.
    //       Element at current position is not last in list.
    // Post: Current position is updated to next position.
    //       item is a copy of element at current position.


 
private:
    int length;
    int currentPos;
    ItemType data[MAX_LENGTH];
};

#endif
