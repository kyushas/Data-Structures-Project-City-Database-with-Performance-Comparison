#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream> 
#include "utils.h"
#include "list.h"

//Array-based list implementation
template <typename E> 
class AList : public List<E> {
    private:
        int maxSize;                //Maximum size of the list
        int listSize;               //Number of current list items
        int curr;                   //Position of current element
        E* listArray;               //Array holding list elements

    public: 
        AList(int size = defaultSize) {    //Constructor
            maxSize = size;
            listSize = curr = 0;
            listArray = new E[maxSize];
        }

        ~AList() { delete[] listArray; }   //Destructor

        void clear() {                     //Reinitialize the list
            delete[] listArray;            //Remove the array
            listSize = curr = 0;           //Reset the size
            listArray = new E[maxSize];    //Recreate array
        }

        //Insert "it" in the current position
        void insert(const E& it) {
            Assert(listSize < maxSize, "List capacity exceeded");
            for(int i = listSize; i > curr; i--) //Shift elements up to make room
                listArray[i] = listArray[i-1];  
            listArray[curr] = it;
            listSize++;                          //Increment list size
        }

        void append(const E& it) {               //Append it
            Assert(listSize < maxSize, "List capacity exceeded");
            listArray[listSize++] = it;
        }

        //Remove and return the current element
        E remove() {
            Assert((curr >= 0) && (curr < listSize), "No element");
            E it = listArray[curr];              //Copy the element
            for(int i = curr; i < listSize-1; i++) //Shift them down
                listArray[i] = listArray[i+1];
            listSize--;                          //Decrement size
            return it;
        }

        void moveToStart() { curr = 0; }        //Reset position 
        void moveToEnd() { curr = listSize; }   //Set at end
        void prev() { if(curr != 0) curr--; }   //Back up
        void next() { if(curr < listSize) curr++; } //Next

        //Return lists size
        int length() const { return listSize; }

        //Return current position
        int currPos() const { return curr; }

        //Set current list position to "pos"
        void moveToPos(int pos) {
            Assert((pos >= 0) && (pos <= listSize), "Pos out of range");
            curr = pos;
        }

        const E& getValue() const {              //Return current element
            Assert((curr >= 0) && (curr < listSize), "No current element");
            return listArray[curr];
        }

        void print() const {
            for (int i = 0; i < listSize; i++) {
            std::cout << listArray[i] << "\n";
    }
}

};

#endif