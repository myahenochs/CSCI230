// list.cpp
// unsorted - statically allocated array implementation (with iterator)

#include "list.h"

List::List()
{
    length = 0;
    currentPos = -1;
}


void List::MakeEmpty()
{
    length = 0;
    currentPos = -1;
}


bool List::IsFull() const
{
    return (length == MAX_LENGTH);
}

bool List::IsEmpty() const
{
    return (length == 0);
}


int List::Length () const
{
    return length;
}


bool List::Retrieve (ItemType& item) const
{
    int location = 0;
    bool found = false;

         while ((location < length) && (!found))
         {
                  if (item== data[location])
                  {
                     found = true;
		     item = data[location];
	          }
                  else
                     location++;
         }
         return found;

}


bool List::Insert (ItemType item)
// the item is stored in next available space.
{
        if (length<MAX_LENGTH)
        {
           data[length] = item;
           length++;
           return true;
         }
         else
           return false;	
}


bool List::Delete (ItemType item)
// Pre: item's key has been initialized.
{
    int location = 0;
    bool found = false;

         while ((location < length) && (!found))
         {
                        if (item==data[location])
                        {
                               found = true;
                               data[location] = data[length - 1];
                               length--;
                        }
                        else
                                location++;
         }
         return(found);
}


void List::SelSort()
{
	ItemType item;
	int passCount;
	int searchIndx;
	int minIndx;
	
	for (passCount = 0; passCount < length-1; passCount++)
	{
		minIndx = passCount;
		for (searchIndx = passCount+1; searchIndx<length; searchIndx++)
			if (data[searchIndx] < data[minIndx])
				minIndx = searchIndx;
		item = data[minIndx];
		data[minIndx] = data[passCount];
		data[passCount] = item;
	}
}   


bool List::IsPresent (ItemType item) const
{
    int location = 0;
    bool found = false;

         while ((location < length) && (!found))
         {
                        if (item== data[location])
                                found = true;
                        else
                                location++;
         }
         return found;

}

void List::Reset()
// Post: Current position has been initialized.
{
    currentPos=0;
}

void List::GetNextItem(ItemType& item)
// Post:  Current position has been updated; item is current item.
{
  if (currentPos>= 0 && currentPos<length) // protects array index
  {
    item = data[currentPos];
    currentPos = (currentPos+1)%length;
  }
}


